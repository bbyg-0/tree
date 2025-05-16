#ifndef TREE_H
#define TREE_H

#include "common.h"

#include <stdbool.h>

typedef struct tree *treeAddress;
typedef char * name;
typedef struct tree{
	treeAddress parentAddress;
	treeAddress prevBrotherAddress;
	treeAddress nextBrotherAddress;
	treeAddress sonAddress;

	name folderName;
}treeNode;

typedef enum{
	inOrder,
	preOrder,
	postOrder,
	byLevel
} traversalType;

void failedMalloc();

unsigned short nbFolders(treeAddress root, unsigned short result);

unsigned short treeHeight(treeAddress root, unsigned short result);

void viewAllFolders(treeAddress parent, traversalType traversal);

void createMemory(treeAddress * folderPointer);

void nodeNaming(treeAddress * currentFolder, name newName);

void showName(treeAddress folder);

treeAddress searchTreeNode(treeAddress currentPath, name target);

void insertTreeNode(treeAddress * parent, treeAddress * son);

void showSons(treeAddress currentPath);

void showCurrentPath(treeAddress currentPath);

void deleteNode(treeAddress * target);

void massDelete(treeAddress * target);

unsigned short getCurrentLevel(treeAddress currentPath);

void deAlokasi (treeAddress * target);

#endif
