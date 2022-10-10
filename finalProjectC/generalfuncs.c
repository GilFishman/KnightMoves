#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"


/*General Functions- */
void MemoryAllocation(void* arr)
{
	if (arr == NULL)
	{
		printf("Memory allocation failed!");
		exit(1);
	}
}
void checkFile(FILE* file)
{
	if (file == NULL)
	{
		printf("File does not exist\n");
		exit(1);
	}
}

/*question 7- printing menu*/
int PrintMenu()
{
	int userSel; 
	printf("1. Enter a knight's stating position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
	scanf("%d", &userSel);
	return userSel;
}
