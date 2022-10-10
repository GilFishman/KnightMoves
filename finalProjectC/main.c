#define _CRT_SECURE_NO_WARNINGS

#include "validmoves.h"
#include "allknightpossiblepaths.h"
#include "SaveToFiles.h"
#include <stdio.h>

void main()
{
	int usersel= PrintMenu();
	char row,col;
	getchar();
	while (usersel < 1 || usersel>6)
	{
		printf("Invalid choise, please choose again-\n");
		usersel = PrintMenu();
	}
	if (usersel == 1)
	{
		scanf("%c%c", &row, &col);
		if (row >= 'A' && row <= 'H')
		{
			if (col >= '1' && col <= '8')
				printf("Valid Position\n");
			else
				printf("InValid Position\n");
		}
		else
			printf("InValid Position!\n");
	}
	else if (usersel == 2)
	{
		scanf("%c%c", &row, &col);
		if (row == NULL || col == NULL)
		{
			printf("please enter stating position\n");
			scanf("%c%c", &row, &col);
		}
		chessPos UserChessPos;
		UserChessPos[0] = row;
		UserChessPos[1] = col;

		pathTree* userTree = findAllPossibleKnightPaths(&UserChessPos);
	}
	else if (usersel == 3)
	{
		scanf("%c%c", &row, &col);
		if (row == NULL || col == NULL)
		{
			printf("please enter stating position\n");
			scanf("%c%c", &row, &col);
		}
		chessPos UserChessPos;
		UserChessPos[0] = row;
		UserChessPos[1] = col;
		pathTree* userTree = findAllPossibleKnightPaths(&UserChessPos);
		chessPosList* coveringAllBoard = findKnightPathCoveringAllBoard(userTree);
		if (coveringAllBoard == NULL)
		{
			printf("There isn't a valid path covering all the board!\n");
		}
	}
	else if (usersel == 4)
	{
		scanf("%c%c", &row, &col);
		if (row == NULL || col == NULL)
		{
			printf("please enter stating position\n");
			scanf("%c%c", &row, &col);
		}
		FILE* NewFile;
		char* File_name;
		printf("please enter file name-\n");
		scanf("%s", &File_name);

		NewFile = fopen(File_name, "wb");
		checkFile(NewFile);

		chessPos UserChessPos;
		UserChessPos[0] = row;
		UserChessPos[1] = col;
		pathTree* userTree = findAllPossibleKnightPaths(&UserChessPos);
		chessPosList* coveringAllBoard = findKnightPathCoveringAllBoard(userTree);
		if (coveringAllBoard == NULL)
		{
			printf("There isn't a valid path covering all the board!\n");
		}

		saveListToBinFile(File_name, coveringAllBoard);
	}
	else if (usersel == 5)
	{
		FILE* NewFile;
		char* File_name;
		printf("please enter file name: ");
		scanf("%s", &File_name);

		NewFile = fopen(File_name, "rb");
		checkFile(NewFile);

		int function6 = checkAndDisplayPathFromFile(File_name);

		if (function6 == -1)
		{
			printf("File not exist");
		}
		else if (function6 == 1)
		{
			printf("The Location list for the knight is not valid");
		}
		else if (function6 == 2)
		{
			printf("There is a valid path covering all the board!");
		}
		else if (function6 == 3)
		{
			printf("There isn't a valid path covering all the board!");
		}

	}
	else if (usersel == 6)
	{
		exit(1);
	}
}