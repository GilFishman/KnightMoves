#pragma once
#include "declarations.h"

typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _chessPosCell
{
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct chessPosList
{
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;


/*question 1 functions*/
chessPosArray*** vaildKnightMoves();
void createChessPos(int row, int col, chessPosArray*** res);

void display(chessPosList* lst);
void DeleteNode(chessPosList* lst, chessPosCell* prev);

void CreateBoard(chessPosList* lst);
void PrintGameBoard(char arr[][Col]);


