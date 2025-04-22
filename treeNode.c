#include "treeNode.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void failedMalloc(){
	printf("\nGAGAL MENGALOKASIKAN MEMORI\n");
}

void createMemory(treeAddress * folderPointer){
	(*folderPointer) = (treeAddress)malloc(sizeof(treeNode));

	if(isEmpty(*folderPointer)){failedMalloc(); return;} 

	(*folderPointer)->parentAddress = NULL;
	(*folderPointer)->prevBrotherAddress = NULL;
	(*folderPointer)->nextBrotherAddress = NULL;
	(*folderPointer)->sonAddress = NULL;

	(*folderPointer)->folderName = NULL;
}

void nodeNaming(treeAddress * currentFolder, name newName){
	(*currentFolder)->folderName = (name)malloc(strlen(newName)+1);
	
	if(isEmpty((*currentFolder)->folderName)){failedMalloc(); return;}
	(*currentFolder)->folderName = newName;
}

treeAddress searchTreeNode(treeAddress currentPath, name target){
	treeAddress temp = currentPath->sonAddress;
	while(!isEmpty(temp)){
		if(strcmp(temp->folderName, target) == 0){
			return temp;
		}
		temp = temp->nextBrotherAddress;
	}
	printf("\nFOLDER TIDAK DITEMUKAN, MENGEMBALIKAN NULL\n");
	return NULL;	
}

void insertTreeNode(treeAddress * parent, treeAddress * son){
	if(isEmpty((*parent)->sonAddress)){
		(*parent)->sonAddress = (*son);
		(*son)->parentAddress = (*parent);
		return;
	}
	treeAddress temp = (*parent)->sonAddress;
	(*parent)->sonAddress = (*son);
	(*son)->parentAddress = (*parent);

	(*son)->nextBrotherAddress = temp;
	temp->prevBrotherAddress = (*son);

}

void showSons(treeAddress currentPath){
	treeAddress temp = currentPath->sonAddress;

	unsigned short i = 0;
	while(!isEmpty(temp)){
		printf("%s\t", temp->folderName);
		temp = temp->nextBrotherAddress;

		i++; if(i % 5 == 0){printf("\n");}
	}
	printf("\n");
}

void showCurrentPath(treeAddress currentPath){
	char buffer1[200] = {0};
	char buffer2[200] = {0};

	treeAddress temp = currentPath;
	while(!isEmpty(temp)){
		strcpy(buffer2, temp->folderName);
		strcat(buffer2, "/");
		strcat(buffer2, buffer1);
		
		strcpy(buffer1, buffer2);

		temp = temp->parentAddress;
	}
	printf("%s\n", buffer1);
}

void deleteNode(treeAddress * target){
	if(!isEmpty((*target)->sonAddress)){printf("\nTHIS FOLDER IS NOT EMPTY\n"); return;}
	if(isEmpty((*target)->prevBrotherAddress)){
		treeAddress temp = (*target)->parentAddress;
		treeAddress temp1 = (*target)->nextBrotherAddress;

		temp->sonAddress = temp1;
		temp1->prevBrotherAddress = NULL;

		(*target)->nextBrotherAddress = NULL;
		(*target)->parentAddress = NULL;
		deAlokasi(target);
		return;
	}
	if(isEmpty((*target)->nextBrotherAddress)){
		treeAddress temp = (*target)->prevBrotherAddress;

		temp->nextBrotherAddress = NULL;

		(*target)->prevBrotherAddress = NULL;
		(*target)->parentAddress = NULL;
		deAlokasi(target);
		return;
	}
	treeAddress temp = (*target)->prevBrotherAddress;
	treeAddress temp1 = (*target)->nextBrotherAddress;

	temp->nextBrotherAddress = temp1;
	temp1->prevBrotherAddress = temp;

	(*target)->nextBrotherAddress = NULL;
	(*target)->prevBrotherAddress = NULL;
	(*target)->parentAddress = NULL;

	deAlokasi(target);
}

unsigned short getCurrentLevel(treeAddress currentPath){
	unsigned short result = 0;

	treeAddress temp = currentPath;
	while(!isEmpty(temp)){
		temp = temp->parentAddress;
		result++;
	}
	result--;

	return result;
}

bool isEmpty(void * currentPath){
	return (currentPath == NULL);
}

void deAlokasi (treeAddress * target){
	if(isEmpty(*target)) return;

	free(*target);
	(*target) = NULL;
}
