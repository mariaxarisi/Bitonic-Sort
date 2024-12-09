#include <../include/bitonic.h>

Sequence bmerge(Sequence b, bool order){
    int n = b.size;
    int m = n/2;
    int* arr = b.arr;

    if(n == 1){
        return b;
    }

    Sequence min = create_sequence(m);
    Sequence max = create_sequence(m);

    for(int i = 0; i < m; i++){
        if(arr[i] > arr[i+m]){
            min.arr[i] = arr[i+m];
            max.arr[i] = arr[i];
        } else {
            min.arr[i] = arr[i];
            max.arr[i] = arr[i+m];
        }
    }

    min = bmerge(min, order);
    max = bmerge(max, order);

    for(int i = 0; i < m; i++){
        if(order){
            arr[i] = min.arr[i];
            arr[i+m] = max.arr[i];
        } else {
            arr[i] = max.arr[i];
            arr[i+m] = min.arr[i];
        }
    }

    destroy_sequence(min);
    destroy_sequence(max);

    return b;
}