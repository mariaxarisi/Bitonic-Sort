#include <../include/bitonic.h>
#include <../include/sequence.h>

#include <mpi.h>

int main(int argc, char *argv[])
{

    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        printf("Error: Invalid arguments\n");
        return 1;
    }

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sizeSeq = atoi(argv[1]);
    sizeSeq = 1 << sizeSeq;

    //Create a random local sequence
    srand(time(NULL) + rank);
    Sequence local = randomSeq(sizeSeq);

    //Distributed bitonic sort
    double start = MPI_Wtime();

    firstSort(local, ascdesc(rank, 0));

    for (int stage = 1; stage <= log2(size); stage++)
    {
        for (int step = stage; step > 0; step--)
        {
            int distance = 1 << (step - 1);
            int partner_rank = partner(rank, distance);
            Sequence remote = exchange(partner_rank, local);
            minmax(rank, stage, distance, local, remote);
            deleteSeq(remote);
        }
        elbowSort(local, ascdesc(rank, stage));
    }

    double end = MPI_Wtime();

    //Check if the sequence is sorted
    bool sorted = isSortedMPI(local, rank, size);
    bool *all_sorted = NULL;

    if(rank == 0){
        all_sorted = (bool *)malloc(size * sizeof(bool));
    }

    MPI_Gather(&sorted, 1, MPI_C_BOOL, rank == 0 ? all_sorted : NULL, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

    if(rank == 0){
        bool is_sorted = true;
        for(int i = 0; i < size; i++){
            if(!all_sorted[i]){
                is_sorted = false;
                break;
            }
        }

        if(is_sorted){
            printf("Sorted Sequence\n");
        }else{
            printf("Not Sorted Sequence\n");
        }
        free(all_sorted);
    }
    
    //Prin the execution time
    if (rank == 0)
    {
        printf("Time: %f sec\n", end - start);
    }

    //Print the sorted sequence
    char c;
    if (rank == 0){
        printf("Do you want to print the sorted sequence? (y/n): ");
        while (scanf(" %c", &c) != 1 || (c != 'y' && c != 'n')) {
            printf("Error: Invalid input. Please enter 'y' or 'n': ");
            while (getchar() != '\n');
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&c, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if (c == 'y'){
        Sequence result;
        if(rank == 0){
            result = createSeq(sizeSeq*size);
        }
        MPI_Gather(local.arr, sizeSeq, MPI_INT, rank == 0 ? result.arr : NULL, sizeSeq, MPI_INT, 0, MPI_COMM_WORLD);
        if(rank == 0){
            printSeq(result);
            deleteSeq(result);
        }
    }

    deleteSeq(local);
    MPI_Finalize();

    return 0;
}