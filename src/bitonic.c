#include <../include/bitonic.h>
#include <../include/sequence.h>

//Finds the partner of the process depending on the distance
int partner(int rank, int distance) {
    return rank ^ distance;
}

//Determines if the process should sort in ascending or descending order (true -> ascending, false -> descending)
bool ascdesc(int rank, int stage) {
    return (rank & (1 << stage)) == 0;
}

//Compares the elements of the local and remote sequences and keeps the min or max elements depending on the stage and distance
void minmax(int rank, int stage, int distance, Sequence local, Sequence remote) {

  int mirror = 1 << stage;
  int w = 2*mirror;
  int pos = rank % w;

  int reflection = pos<mirror ? mirror-pos-1 : pos-mirror; 

  if (reflection & (1 << (int)log2(distance))) {
    // Keep min elements (pairwise)
        for(int i = 0; i < local.size; i++) {
            if(local.arr[i] > remote.arr[i]) {
                local.arr[i] = remote.arr[i];
            }
        }
    return;
  } else {
    // Keep max elements (pairwise)
        for(int i = 0; i < local.size; i++) {
            if(local.arr[i] < remote.arr[i]) {
                local.arr[i] = remote.arr[i];
            }
        }
    return;
  }
}

//Sends the local sequence to the partner process and receives the remote sequence from the partner process
Sequence exchange(int partner, Sequence local){
    Sequence remote = createSeq(local.size);
    MPI_Send(local.arr, local.size, MPI_INT, partner, 0, MPI_COMM_WORLD);
    MPI_Recv(remote.arr, local.size, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return remote;
}

int compareAsc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int compareDesc(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}

//Sorts the local sequence in ascending or descending order when the stage is 0
void firstSort(bool order, Sequence local){
    if(order){
        qsort(local.arr, local.size, sizeof(int), compareAsc);
    } else {
        qsort(local.arr, local.size, sizeof(int), compareDesc);
    }
}

//TODO: Implement the elbowsort algorithm for the next sorting steps (O(n))
