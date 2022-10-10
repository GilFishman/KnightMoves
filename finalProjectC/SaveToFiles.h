#include "declarations.h"

#include "allknightpossiblepaths.h"
#include "validmoves.h"
#include <stdbool.h>
/*question 5 functions-*/
short int CountList(chessPosList* pos_list);
void saveListToBinFile(char* file_name, chessPosList* pos_list);
void checkAndWriteToFile(int* counter, FILE* locationFile, BYTE* byte);
void writeLastByte(int* counter, FILE* locationFile, BYTE* byte);
bool isBitSet(BYTE byte, int index);

/*question 6 functions-*/
#define FILE_NOT_EXISTS -1
#define PATH_NOT_VALID 1
#define ALL_THE_BOARD_IS_COVERED 2
#define ALL_THE_BOARD_IS_NOT_COVERED 3
int checkAndDisplayPathFromFile(char* file_name);
chessPosList* CreateListFromLocationFile(FILE* locationFile);
void checkAndReadToFile(int* counter, FILE* locationFile, BYTE* byte);
bool checkIsValid(chessPosList* lst);


