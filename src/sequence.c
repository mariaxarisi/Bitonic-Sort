#include <../include/sequence.h>

Sequence createSeq(int size){
    Sequence s;
    s.size = size;
    s.arr = (int*)malloc(size*sizeof(int));
    return s;
}

Sequence randomSeq(int size){
    Sequence s = createSeq(size);
    for(int i = 0; i < size; i++){
        s.arr[i] = rand() % 100;
    }
    return s;
}

void printSeq(Sequence s){
    for(int i = 0; i < s.size; i++){
        printf("%d ", s.arr[i]);
    }
    printf("\n");
}

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