#include <../include/bitonic.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[]){
    
    if (argc != 2 || atoi(argv[1]) <= 0){
        printf("Error: Invalid arguments\n");
        return 1;
    }

    int n = 1 << atoi(argv[1]);

    Sequence s1 = random_sequence(n);

    printf("-----------Serial Bitonic Sort-----------\n");
    
    clock_t start = clock();
    s1 = bsort(s1, true);
    clock_t end = clock();

    if(isSorted(s1)){
        printf("Sorted Sequence\n");
    } else {
        printf("Not Sorted Sequence\n");
    }

    printf("Time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    destroy_sequence(s1);

    Sequence s2 = random_sequence(n);

    printf("-----------QSort-----------\n");

    start = clock();
    qsort(s2.arr, s2.size, sizeof(int), compare);
    end = clock();

    if(isSorted(s2)){
        printf("Sorted Sequence\n");
    } else {
        printf("Not Sorted Sequence\n");
    }

    printf("Time: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

    destroy_sequence(s2);

    return 0;
}