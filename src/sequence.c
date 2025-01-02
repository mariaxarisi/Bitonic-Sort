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

// TODO: Implement the isSorted function using MPI in order to prevent O(n) complexity
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

    int globalMin, globalMax;
    int neighborFirst;

    MPI_Allreduce(&firstLocal, &globalMin, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&lastLocal, &globalMax, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

    // Check that the first element of rank 0 is the global minimum
    if (rank == 0 && firstLocal != globalMin)
    {
        return false;
    }

    // Check that the last element of rank (size - 1) is the global maximum
    if (rank == size - 1 && lastLocal != globalMax)
    {
        return false;
    }

    // Check that the last element of the current process is <= the first element of the next process
    if (rank < size - 1)
    {
        MPI_Send(&lastLocal, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&neighborFirst, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (lastLocal > neighborFirst)
        {
            return false;
        }
    }

    return true;
}

void deleteSeq(Sequence s)
{
    free(s.arr);
}