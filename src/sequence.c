#include <../include/sequence.h>

Sequence createSeq(int size)
{
    Sequence s;
    s.size = size;
    s.arr = (int *)malloc(size * sizeof(int));
    if (s.arr == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for sequence of size %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    return s;
}

Sequence randomSeq(int size)
{
    Sequence s = createSeq(size);
    for (int i = 0; i < size; i++)
    {
        s.arr[i] = rand() % 4000;
    }
    return s;
}

void printSeq(Sequence s)
{
    for (int i = 0; i < s.size; i++)
    {
        printf("%d ", s.arr[i]);
    }
    printf("\n");
}

bool isSortedSequential(Sequence s)
{
    for (int i = 0; i < s.size - 1; i++)
    {
        if (s.arr[i] > s.arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

bool isSortedMPI(Sequence local, int rank, int size)
{
    int firstLocal = local.arr[0];
    int lastLocal = local.arr[local.size - 1];
    int neighborLast;

    if(!isSortedSequential(local)){
        return false;
    }

    if(rank == 0){
        MPI_Send(&lastLocal, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }
    else if(rank == size - 1){
        MPI_Recv(&neighborLast, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(neighborLast > firstLocal){
            return false;
        }
    }
    else{
        MPI_Sendrecv(&lastLocal, 1, MPI_INT, rank + 1, 0, &neighborLast, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(neighborLast > firstLocal){
            return false;
        }
    }

    return true;
}

void deleteSeq(Sequence s)
{
    free(s.arr);
}