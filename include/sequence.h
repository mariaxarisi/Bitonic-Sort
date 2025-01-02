#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>

typedef struct
{
    int *arr;
    int size;
} Sequence;

Sequence createSeq(int size);
Sequence randomSeq(int size);
void printSeq(Sequence s);
bool isSortedSequential(Sequence s);
bool isSortedMPI(Sequence local, int rank, int size);
void deleteSeq(Sequence s);

#endif