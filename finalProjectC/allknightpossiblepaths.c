#define _CRT_SECURE_NO_WARNINGS
#include "allknightpossiblepaths.h"

/*question 3 functions- findAllPossibleKnightPaths, Fheleper*/
pathTree* findAllPossibleKnightPaths(chessPos* statingPosition)
{
	pathTree* path_tree = (pathTree*)malloc(sizeof(path_tree));
	chessPosArray*** mat = vaildKnightMoves();
	bool path[Row][Col];
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			path[i][j] = false;
		}
	}

	path_tree->root = Fheleper(statingPosition, mat, path);
	return path_tree;

}
treeNode* Fheleper(chessPos* startingPosition, chessPosArray*** mat, bool path[Row][Col])
{
	/*base case*/
	int r, c,kidR,kidC;
	r = (*startingPosition)[0] - 'A';
	c = (*startingPosition)[1] - '1';
	int size = mat[r][c]->size;
	int count = 0;
	
	for (int i = 0; i < size; i++)
	{
		kidR = mat[r][c]->positions[i][0] - 'A';
		kidC = mat[r][c]->positions[i][1] - '1';
		if (path[kidR][kidC] == true)
			count++;
	}
	if (count == size)
	{
		return createNewTreeNode(*startingPosition, NULL);
	}
	
	/*recursive step*/
	treeNode* kid;
	treeNode* tr = createNewTreeNode(*startingPosition, NULL);
	path[r][c] = true;
	for (int i = 0; i < size; i++)
	{
		kidR = mat[r][c]->positions[i][0] - 'A';
		kidC = mat[r][c]->positions[i][1] - '1';
		if (path[kidR][kidC] == false)
		{
			kid = Fheleper(&(mat[r][c]->positions[i]), mat, path);
			insertCellToHead(tr, createNewListCell(kid, NULL));
		}
	}
	path[r][c] = false;
	return tr;
}

treeNode* createNewTreeNode(chessPos positions, treeNodeListCell* next)
{
	treeNode* res;
	res = (treeNode*)malloc(sizeof(treeNode));
	MemoryAllocation(res);
	res->position[0] = positions[0];
	res->position[1] = positions[1];

	res->next_possible_positions = next;
	return res;
}


treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* next)
{
	treeNodeListCell* newNode;
	newNode = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	MemoryAllocation(newNode);
	newNode->node = node;
	newNode->next = next;
	return newNode;
}
void insertCellToHead(treeNode* treeNode, treeNodeListCell* head)
{
	head->next = treeNode->next_possible_positions;
	treeNode->next_possible_positions = head;
}

/*question 4 functions- findKnightPathCoveringAllBoard,findknightHelper,freeCPList*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	int currSize = 0;
	chessPos posArr[Row * Col];
	bool isListReady = false;
	chessPosArray*** chessPosArr = vaildKnightMoves();
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	MemoryAllocation(lst);

	makeEmptyList(lst);

	findKnightHelper(path_tree->root, lst, &isListReady, chessPosArr, posArr, &currSize);
	if (isListReady == true)
	{
		return lst;
	}
	else
	{
		free(lst);
		return NULL;
	}
}

void findKnightHelper(treeNode* root, chessPosList* lst, bool* isListReady, chessPosArray*** arr, chessPos* posArr, int* currSize)
{
	int i;
	treeNodeListCell* curr;
	if (root == NULL)
		return;

	posArr[*currSize][0] = root->position[0];
	posArr[*currSize][1] = root->position[1];
	(*currSize)++;

	if (*currSize == Row * Col && *isListReady == false)
	{
		for (i = 0; i < Row * Col; i++)
		{
			insertCellToEndOfList(lst, createChessPosCell(posArr[i], NULL));
		}
		*isListReady = true;
		(*currSize)--;
		return;
	}

	curr = root->next_possible_positions;
	while (curr) {
		findKnightHelper(curr->node, lst, isListReady, arr, posArr, currSize);
		curr = curr->next;
	}

	(*currSize)--;
	return;

}


void makeEmptyList(chessPosList* lst) {
	lst->head = lst->tail = NULL;
}
int isEmptyList(chessPosList* lst)
{
	if (lst->head == NULL)
		return 1;
	else
		return 0;
}
void insertCellToEndOfList(chessPosList* lst, chessPosCell* node)
{
	node->next = NULL;
	if (isEmptyList(lst) == 1)
	{
		lst->head = lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;

	}
}

chessPosCell* createChessPosCell(chessPos position, chessPosCell* next)
{
	chessPosCell* cell = (chessPosCell*)malloc(sizeof(chessPosCell));
	MemoryAllocation(cell);
	cell->position[0] = position[0];
	cell->position[1] = position[1];
	cell->next = next;
	return cell;

}


void freeCPList(chessPosList* lst)
{
	chessPosCell* curr, * next;
	curr = lst->head;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(lst);
}
