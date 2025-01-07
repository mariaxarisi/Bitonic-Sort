#ifndef BITONIC_H
#define BITONIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* arr;
    int size;
} Sequence;

Sequence create_sequence(int size);
Sequence random_sequence(int size);
void destroy_sequence(Sequence s);
bool isSorted(Sequence s);
void print_sequence(Sequence s);

Sequence bmerge(Sequence b, bool order);
Sequence bsort(Sequence b, bool order);

#endif