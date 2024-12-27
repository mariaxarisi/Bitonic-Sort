#include <../include/bitonic.h>
#include <../include/sequence.h>

#include <mpi.h>

int main(int argc, char *argv[]) {

    if(argc != 2 || atoi(argv[1]) < 0) {
        printf("Error: Invalid arguments\n");
        return 1;
    }

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sizeSeq = atoi(argv[1]);
    sizeSeq = 1 << sizeSeq;
    srand(time(NULL) + rank);
    Sequence local = randomSeq(sizeSeq);

    double start = MPI_Wtime();

    firstSort(ascdesc(rank, 0), local);
    for(int stage = 1; stage <= log2(size); stage++) {
        for(int step = stage; step > 0; step--) {
            int distance = 1 << (step - 1);
            int partner_rank = partner(rank, distance);
            Sequence remote = exchange(partner_rank, local);
            minmax(rank, stage, distance, local, remote);
            deleteSeq(remote);
        }
        //TODO: Implement the elbowSort function and use this instead of the firstSort function
        firstSort(ascdesc(rank, stage), local);
    }

    Sequence result;
    if (rank == 0) {
        result = createSeq(sizeSeq * size);
    }

    MPI_Gather(local.arr, sizeSeq, MPI_INT, rank == 0 ? result.arr : NULL, sizeSeq, MPI_INT, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0) {
        printSeq(result);
        if(isSorted(result)){
            printf("\nSorted Sequence\n");
        } else {
            printf("\nNot Sorted Sequence\n");
        }
        deleteSeq(result);
        printf("Execution Time: %f\n", end - start);
    }

    deleteSeq(local);
    MPI_Finalize();

    return 0;
}