#include <../include/bitonic.h>

int main(){
    
    int n;
    printf("Enter a number N and a sequence of 2^N elements will be generated: ");
    while(scanf("%d", &n) != 1 || n < 1){
        printf("Invalid input. Please enter a number >= 1: ");
        while(getchar() != '\n');
    }
    n = (2 << (n - 1));

    Sequence s = random_sequence(n);

    printf("Generated sequence: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", s.arr[i]);
    }
    printf("\n");

    s = bsort(s, true);

    printf("Sorted sequence: \n");
    for(int i = 0; i < n; i++){
        printf("%d ", s.arr[i]);
    }
    printf("\n");

    destroy_sequence(s);

    return 0;
}