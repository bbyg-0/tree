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

void showName(treeAddress folder){
	if(isEmpty(folder)) return;
	printf("%s\n", folder->folderName);
}

void nodeNaming(treeAddress * currentFolder, name newName){
	(*currentFolder)->folderName = (name)malloc(strlen(newName)+1);
	
	if(isEmpty((*currentFolder)->folderName)){failedMalloc(); return;}
	(*currentFolder)->folderName = newName;
}

//mencari dan mengembalikan son sampai ke bawah-bawah nya
treeAddress searchTreeNode(treeAddress currentPath, name target){
	//cek kalo si currentPath itu bukan NULL dan punya anak
	if(isEmpty(currentPath) || isEmpty((currentPath)->sonAddress)) return NULL;

	//quick search ke son yang deket-deket
	treeAddress temp = searchTreeNodeSon(currentPath, target);
	//kalo ternyata beneran ada, langsung direturn aja
	if(!isEmpty(temp)) return temp;

	treeAddress temp1 = temp;
	//nyari son yang punya anak
	temp = notLeafSon(currentPath);

	while(temp != currentPath){
		//cadangan
		temp1 = temp;
		//nyari son yang punya anak
		temp = notLeafSon(temp);
		printf("%s\n", temp->folderName);

		//null kalo ternyata si temp itu leaf
		if(isEmpty(temp)){
			temp = temp1->parentAddress;
			if(!isEmpty(temp)) temp = temp->nextBrotherAddress;
		}

		//kalo misal semua son nya gak pada punya anak
		else if(temp == temp1){
			treeAddress son = temp->sonAddress;

			//quick search ke son dari temp, karena temp gak punya
			//son yang punya anak lagi
			son = searchTreeNodeSon(temp, target);
		
			//kalo ternyata beneran ada, langsung direturn aja
			if(!isEmpty(son)) return son;

			//kalo gak ada, temp bakal dipindahin ke brothernya
			temp = (temp)->nextBrotherAddress;

			//kalo ternyata dia adalah brother paling ujung,
			//maka dia bakal dikembaliin ke parent nya
			if(isEmpty(temp)) temp = temp->parentAddress;
			//tapi kalo bukan, diquick search dulu
			else{
				son = searchTreeNodeSon(temp, target);
				if(!isEmpty(son)) return son;	}}

		//kalo masih punya son yang punya anak,
		//coba buat quick search dulu, siapa tau ada
		else{
			treeAddress son = temp->sonAddress;
			son = searchTreeNode(temp, target);
			
			if(!isEmpty(son)) return  son;
			temp = (temp)->nextBrotherAddress;
		}
	}

	printf("\nFOLDER TIDAK DITEMUKAN, MENGEMBALIKAN NULL\n");
	return NULL;	
}

//mencari dan mengembalikan target hanya sampai son saja, gak sampai bawah-bawah nya
treeAddress searchTreeNodeSon(treeAddress currentPath, name target){
	if(isEmpty(currentPath) || isEmpty((currentPath)->sonAddress)) return NULL;

	currentPath = (currentPath)->sonAddress;
	while(!isEmpty(currentPath)){
		if(strcmp(currentPath->folderName, target) == 0) return currentPath;

		currentPath = currentPath->nextBrotherAddress;
	}

	return NULL;
}

//mengembalikan son pertama yang memiliki anak
treeAddress notLeafSon(treeAddress parent){
	if(isEmpty(parent) || isEmpty((parent)->sonAddress)) return NULL;
	treeAddress temp = parent->sonAddress;

	while(!isEmpty(temp)){
		if(!isEmpty(temp->sonAddress)) return temp;

		temp = temp->nextBrotherAddress;
	}
	return parent;
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
	if(isEmpty(currentPath)) return;
	treeAddress temp = currentPath->sonAddress;

	unsigned short i = 0;
	printf("FOLDER:\n");
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
	if(isEmpty(*target)){printf("\nNULL POINTER\n"); return;}
	if(!isEmpty((*target)->sonAddress)){printf("\nTHIS FOLDER IS NOT EMPTY\n"); return;}
	if(isEmpty((*target)->prevBrotherAddress) && isEmpty((*target)->nextBrotherAddress)){
		treeAddress temp = (*target)->parentAddress;
		temp->sonAddress = NULL;
		(*target)->parentAddress = NULL;


		deAlokasi(target);
		return;
	}
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

void massDelete(treeAddress * target){
	if(isEmpty(*target) || isEmpty((*target)->sonAddress)){return;}

	treeAddress temp = (*target)->sonAddress;
	treeAddress temp1 = NULL;
	while(!isEmpty((*target)->sonAddress)){
		temp1 = temp->nextBrotherAddress;
		deleteNode(&temp);
		temp = temp1;
	}
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
