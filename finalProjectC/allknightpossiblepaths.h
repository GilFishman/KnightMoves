#pragma once
#include "validmoves.h"
#include "declarations.h"


typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell
{
	treeNode* node;
	struct _treeNodeListcell* next;
} treeNodeListCell;

typedef struct _pathTree
{
	treeNode* root;
}pathTree;


/*question 3 functions- findAllPossibleKnightPaths, Fheleper*/
pathTree* findAllPossibleKnightPaths(chessPos* statingPosition);
treeNode* Fheleper(chessPos* startingPosition, chessPosArray*** mat, bool path[Row][Col]);
treeNode* createNewTreeNode(chessPos positions, treeNodeListCell* next);
treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* next);
void insertCellToHead(treeNode* treeNode, treeNodeListCell* head);

/*question 4 functions- findKnightPathCoveringAllBoard,findknightHelper,freeCPList*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosCell* createChessPosCell(chessPos position, chessPosCell* next);
void insertCellToEndOfList(chessPosList* lst, chessPosCell* node);
void makeEmptyList(chessPosList* lst);
void findKnightHelper(treeNode* root, chessPosList* lst, bool* isListReady, chessPosArray*** arr, chessPos* posArr, int* currSize);
int isEmptyList(chessPosList* lst);
void freeCPList(chessPosList* lst);




