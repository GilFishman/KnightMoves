#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define Col 5
#define Row 5
#define MaxPositionsForArray 8
typedef unsigned char BYTE;

typedef char chessPos[2];

void MemoryAllocation(void* arr);
void checkFile(FILE* file);
int PrintMenu();
