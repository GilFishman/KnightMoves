#define _CRT_SECURE_NO_WARNINGS

#include "validmoves.h"


/*question 1 functions-validknightmoves,createChessPos*/

chessPosArray*** vaildKnightMoves()
{
	chessPosArray*** res;
	int i, j;

	res = (chessPosArray***)malloc(sizeof(chessPosArray**) * Row);
	MemoryAllocation(res);
	for (i = 0; i < Row; i++)
	{
		res[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * Col);
		MemoryAllocation(res[i]);
		for (j = 0; j < Col; j++)
		{
			res[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
			MemoryAllocation(res[i][j]);
			res[i][j]->positions = (chessPos*)malloc(sizeof(chessPos) * MaxPositionsForArray);
			MemoryAllocation(res[i][j]->positions);
			res[i][j]->size = MaxPositionsForArray;
			createChessPos(i, j, res);
		}
	}
	return res;
}

void createChessPos(int row, int col, chessPosArray*** res)
{
	int size = 0;
	int i = 0;

	if (row - 2 >= 0)
	{
		if (col + 1 < Col)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row - 2 + 'A';
			res[row][col]->positions[i][1] = (char)col + 1 + '1';
			i++;
		}
		if (col - 1 >= 0)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row - 2 + 'A';
			res[row][col]->positions[i][1] = (char)col - 1 + '1';
			i++;
		}
	}
	if (row + 2 < Row)
	{
		if (col + 1 < Col)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row + 2 + 'A';
			res[row][col]->positions[i][1] = (char)col + 1 + '1';
			i++;
		}
		if (col - 1 >= 0)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row + 2 + 'A';
			res[row][col]->positions[i][1] = (char)col - 1 + '1';
			i++;
		}
	}
	if (col + 2 < Col)
	{
		if (row - 1 >= 0)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row - 1 + 'A';
			res[row][col]->positions[i][1] = (char)col + 2 + '1';
			i++;
		}
		if (row + 1 < Row)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row + 1 + 'A';
			res[row][col]->positions[i][1] = (char)col + 2 + '1';
			i++;
		}
	}
	if (col - 2 >= 0)
	{
		if (row - 1 >= 0)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row - 1 + 'A';
			res[row][col]->positions[i][1] = (char)col - 2 + '1';
			i++;
		}
		if (row + 1 < Row)
		{
			size++;
			res[row][col]->positions[i][0] = (char)row + 1 + 'A';
			res[row][col]->positions[i][1] = (char)col - 2 + '1';
			i++;
		}
	}
	res[row][col]->positions = (chessPos*)realloc(res[row][col]->positions, sizeof(chessPos) * size);
	MemoryAllocation(res[row][col]->positions);

	res[row][col]->size = size;
}


/*question 2 functions- Display, DeleteNode,CreateBoard,PrintGameBoard*/
void display(chessPosList* lst)
{
	
	chessPosCell* curr = lst->head;
	chessPosCell* prev = NULL;
	chessPosCell* next;

	bool ispresent[Row][Col];
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			ispresent[i][j] = false;
		}
	}

	while (curr != NULL)
	{
		if (ispresent[curr->position[0]-'A'][curr->position[1]-'1'] == true)
		{
			next = curr->next;
			DeleteNode(lst, prev);
			curr = next;
		}
		else
		{
			ispresent[curr->position[0]-'A'][curr->position[1]-'1'] = true;
			prev = curr;
			curr = curr->next;
		}
	}
	
	CreateBoard(lst);
}

void DeleteNode(chessPosList* lst, chessPosCell* prev)
{
	chessPosCell* temp;
	if (prev->next == lst->tail) {
		free(prev->next);
		lst->tail = prev;
		prev->next = NULL;
	}
	else
	{
		temp = prev->next;
		prev->next = temp->next;
		free(temp);
	}
}

void CreateBoard(chessPosList* lst)
{
	int lstIndex = 1;
	char arr[Row][Col];
	chessPosCell* curr = lst->head;
	int row, col;
	while (curr != NULL)
	{
		row = curr->position[0]-'A';
		col = curr->position[1]-'1';
		arr[row][col] = lstIndex;
		lstIndex++;
		curr = curr->next;
	}
	PrintGameBoard(arr);
}

void PrintGameBoard(char arr[][Col])
{
	int i, j;
	printf("\n\t");
	for (i = 1; i <= Row; i++)
		printf("%d\t", i);
	printf("\n    ");
	for (i = 0; i <= Row * Col; i++)
		printf("_");
	printf("\n\n");
	for (i = 0; i < Row; i++)
	{
		printf("%c   |\t", i + 'A');
		for (j = 0; j < Col; j++)
			printf("%2d   |\t", arr[i][j]);
		printf("\n");
	}
	printf("    ");
	for (i = 0; i <= Row * Row; i++)
		printf("_");
	printf("\n");
}