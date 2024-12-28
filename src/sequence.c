#include <../include/sequence.h>

Sequence createSeq(int size){
    Sequence s;
    s.size = size;
    s.arr = (int*)malloc(size*sizeof(int));
    if (s.arr == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for sequence of size %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    return s;
}

Sequence randomSeq(int size){
    Sequence s = createSeq(size);
    for(int i = 0; i < size; i++){
        s.arr[i] = rand() % 4000;
    }
    return s;
}

void printSeq(Sequence s){
    for(int i = 0; i < s.size; i++){
        printf("%d ", s.arr[i]);
    }
    printf("\n");
}

//TODO: Implement the isSorted function using MPI in order to prevent O(n) complexity
bool isSorted(Sequence s){
    for(int i = 0; i < s.size - 1; i++){
        if(s.arr[i] > s.arr[i + 1]){
            return false;
        }
    }
    return true;
}

void deleteSeq(Sequence s){
    free(s.arr);
}