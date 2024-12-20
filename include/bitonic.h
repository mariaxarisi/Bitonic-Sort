#ifndef BITONIC_H
#define BITONIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <mpi.h>
#include "sequence.h"

int partner(int rank, int distance);
bool ascdesc(int rank, int stage);
void minmax(int rank, int stage, int distance, Sequence local, Sequence remote);
Sequence exchange(int partner, Sequence local);
int compareAsc(const void *a, const void *b);
int compareDesc(const void *a, const void *b);
void firstSort(bool order, Sequence local);

#endif