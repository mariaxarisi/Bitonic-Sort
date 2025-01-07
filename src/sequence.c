#include <../include/bitonic.h>

#include <time.h>

Sequence create_sequence(int size){
    Sequence s;
    s.size = size;
    s.arr = (int*)malloc(size*sizeof(int));
    return s;
}

Sequence random_sequence(int size){
    Sequence s = create_sequence(size);
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        s.arr[i] = rand() % 100;
    }
    return s;
}

void print_sequence(Sequence s){
    for(int i = 0; i < s.size; i++){
        printf("%d ", s.arr[i]);
    }
    printf("\n");
}

bool isSorted(Sequence s){
    for(int i = 0; i < s.size - 1; i++){
        if(s.arr[i] > s.arr[i+1]){
            return false;
        }
    }
    return true;
}

void destroy_sequence(Sequence s){
    free(s.arr);
}