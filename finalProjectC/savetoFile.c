#define _CRT_SECURE_NO_WARNINGS
#include "SaveToFiles.h"

/*question 5 functions-IsBitSet,checkAndWriteToFile,writeLastByte,saveListToBinFile,CountList */

bool isBitSet(BYTE byte, int index)
{
	BYTE mask = 0x01 << (index);
	if (byte & mask)
		return true;
	else
		return false;
}

void checkAndWriteToFile(int* counter, FILE* locationFile, BYTE* byte)
{
	if (*counter == 8)
	{
		*counter = 0;
		fwrite(byte, sizeof(BYTE), 1, locationFile);
		*byte = 0;
	}
}
void writeLastByte(int* counter, FILE* locationFile, BYTE* byte)
{
	if (*counter != 8)
		*byte = *byte << (8-*counter);

	fwrite(byte, sizeof(BYTE), 1, locationFile);
}

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	short int ListSize = CountList(pos_list);
	BYTE position0, position1;
	FILE* locationFile = fopen(file_name, "wb");
	checkFile(locationFile);
	int i, counter = 0;

	fwrite(&ListSize, sizeof(short int), 1, locationFile);

	chessPosCell* curr = pos_list->head;
	BYTE byte = 0;

	while (curr != NULL)
	{
		position0 = curr->position[0] - 'A';
		position1 = curr->position[1] - '1';

		for (i = 2; i >= 0; i--)
		{
			checkAndWriteToFile(&counter, locationFile, &byte);

			byte <<= 1;
			if (isBitSet(position0, i))
				byte = byte | 1;
			counter++;
		}
		for (i = 2; i >= 0; i--)
		{
			checkAndWriteToFile(&counter, locationFile, &byte);

			byte <<= 1;
			if (isBitSet(position1, i))
				byte = byte | 1;
			counter++;
		}

		curr = curr->next;
	}
	writeLastByte(&counter, locationFile, &byte);
	fclose(locationFile);
}

short int CountList(chessPosList* pos_list)
{
	chessPosCell* curr = pos_list->head;
	int count = 0;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

/*question 6 functions-CreateListFromLocationFile */
chessPosList* CreateListFromLocationFile(FILE* locationFile)
{
	chessPosList* lst;
	short int ListSize;
	BYTE position0, position1;
	chessPos position;
	int i, counter =8;
	int location;
	BYTE byte = 0;
	chessPosCell* curr;

	lst = (chessPosList*)malloc(sizeof(chessPosList));
	makeEmptyList(lst);

	fread(&ListSize, sizeof(short int), 1, locationFile);

	for (location = 0; location < ListSize; location++)
	{
		position0 = 0;
		position1 = 0;

		for (i = 2; i >= 0; i--)
		{
			checkAndReadToFile(&counter, locationFile, &byte);

			position0 <<= 1;
			if (isBitSet(byte, 7-counter))
				position0 = position0 | 1;
			counter++;
		}

		for (i = 2; i >= 0; i--)
		{
			checkAndReadToFile(&counter, locationFile, &byte);

			position1 <<= 1;
			if (isBitSet(byte, 7 - counter))
				position1 = position1 | 1;
			counter++;
		}
		position[0] = position0 + 'A';
		position[1] = position1 + '1';
		curr = createChessPosCell(position, NULL);
		insertCellToEndOfList(lst, curr);
	}
	if (checkIsValid(lst) == false)
	{
		freeCPList(lst);
	}
	return lst;
	
}

bool checkIsValid(chessPosList* lst)
{
	chessPosCell* curr = lst->head; 
	chessPosCell* next = curr->next;
	bool isValid = true; 

	while (isValid == true && curr != NULL)
	{
		char row = curr->position[0] - 'A';
		char col = curr->position[1] - '1';
		char rowNext = next->position[0] - 'A';
		char colNext = next->position[1] - '1';

		if (row - rowNext != 2 && rowNext- row !=2 && row- rowNext !=1 && rowNext-row!=1)
		{
			isValid = false; 
		}
		else if (col - colNext != 2 && colNext - col != 2 && col - colNext != 1 && colNext - col != 1)
		{
			isValid = false; 
		}
	}
	return isValid;

}

void checkAndReadToFile(int* counter, FILE* locationFile, BYTE* byte)
{
	if (*counter == 8)
	{
		*counter = 0;
		fread(byte, sizeof(BYTE), 1, locationFile);
	}
}


int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* locationFile;
	chessPosList* lst;
	
	locationFile = fopen(file_name, "rb");
	if (locationFile == NULL)
		return FILE_NOT_EXISTS;
	
	
	lst = CreateListFromLocationFile( locationFile);

	fclose(locationFile);
	if (lst == NULL)
		return PATH_NOT_VALID;

	display(lst);
	if (CountList(lst) == Row * Col)
	{
		freeCPList(lst);
		return ALL_THE_BOARD_IS_COVERED;

	}
	else
	{
		freeCPList(lst);
		return ALL_THE_BOARD_IS_NOT_COVERED;
	}

}
