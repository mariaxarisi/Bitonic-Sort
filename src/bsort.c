#include <../include/bitonic.h>

Sequence bsort(Sequence b, bool order){
    if(b.size == 1){
        return b;
    }

    int n = b.size;
    int m = n / 2;

    Sequence l = create_sequence(m);
    Sequence r = create_sequence(m);

    for(int i = 0; i < m; i++){
        l.arr[i] = b.arr[i];
        r.arr[i] = b.arr[i + m];
    }

    l = bsort(l, true);
    r = bsort(r, false);

    for(int i = 0; i < m; i++){
        b.arr[i] = l.arr[i];
        b.arr[i + m] = r.arr[i];
    }

    b = bmerge(b, order);

    destroy_sequence(l);
    destroy_sequence(r);

    return b;
}