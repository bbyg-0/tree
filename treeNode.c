#include "treeNode.h"
#include "Q.h"
#include "common.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void failedMalloc(){
	printf("\nGAGAL MENGALOKASIKAN MEMORI\n");
}

unsigned short nbFolders(treeAddress root, unsigned short result){
	if(isEmpty(root)) return result;
	result++;

	treeAddress temp = (root)->sonAddress;	//kalo leaf, temp = NULL
	while(!isEmpty(temp)){
		result = nbFolders(temp, result);
		temp = temp->nextBrotherAddress;
	}

	return result;
}
unsigned short treeHeight(treeAddress root, unsigned short result){
	if(isEmpty(root)) return result;
	
	treeAddress temp = (root)->sonAddress;
	while(!isEmpty(temp)){
		result = nbFolders(temp, result);
		temp = temp->nextBrotherAddress;
		result -= 2;
		printf("%hu\n", result);
	}
	result++;

	return result;
}


void viewAllFolders(treeAddress parent, traversalType traversal){
	switch(traversal){
		case inOrder:{
			if(isEmpty(parent)) return;
			
			treeAddress firstChild = parent->sonAddress;
			if(!isEmpty(firstChild)) {viewAllFolders(firstChild, inOrder);}

			printf("%s\n", parent->folderName); //akses diri sendiri

			if(!isEmpty(firstChild)){
				treeAddress sibling = firstChild->nextBrotherAddress;
				while(!isEmpty(sibling)){
					viewAllFolders(sibling, inOrder);
					sibling = sibling->nextBrotherAddress;
				}
			}
		
			break;
		}
		case preOrder:{
			if(isEmpty(parent)) return;
			printf("%s\n", (parent)->folderName);

			treeAddress temp = (parent)->sonAddress;	//kalo leaf, temp = NULL
			while(!isEmpty(temp)){
				treeAddress next = temp->nextBrotherAddress;	//temp bakal dihapus
				viewAllFolders(temp, preOrder);
				temp = next;
			}

			break;
		}
		case postOrder:{
			if(isEmpty(parent)) return;

			treeAddress temp = (parent)->sonAddress;	//kalo leaf, temp = NULL
			while(!isEmpty(temp)){
				treeAddress next = temp->nextBrotherAddress;	//temp bakal dihapus
				viewAllFolders(temp, postOrder);
				temp = next;
			}
			printf("%s\n", (parent)->folderName);

			break;
		}
		case byLevel:{
			qAddress temp = NULL;
			qAddress head = NULL;

			qCreateMemory(&temp);
			isiQ(&temp, parent);
			insertQ(&head, &temp);

			while(!isEmpty(head)){
				treeAddress current = deQ(&head);
				printf("%s\n", current->folderName);

				treeAddress child = current->sonAddress;
				//if(isEmpty(child))printf("%s gak punya anak\n", current->folderName);
				//else printf("%s punya anak\n", current->folderName);
				if(isEmpty(child)) printf("ASELOLE");
				while(!isEmpty(child)){
					//nge enque si semua anak dari parent
					qCreateMemory(&temp);
					isiQ(&temp, child);
					insertQ(&head, &temp);

					child = child->nextBrotherAddress;
				}
				printf("\n");
			}

			printf("\nBERES\n");

			break;
		}
		default:{
			printf("JENIS TRAVERSAL TIDAK DIKENALI\n");
			break;
		}
	}
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

//mencari dan mengembalikan son sampai ke bawah-bawah nya menggunakan rekursif
treeAddress searchTreeNode(treeAddress currentPath, name target){
	if(isEmpty(currentPath)) return NULL;
	if(strcmp(currentPath->folderName, target) == 0) return currentPath;

	treeAddress temp = currentPath->sonAddress;
	while(!isEmpty(temp)){
		treeAddress result = searchTreeNode(temp, target);
		if(!isEmpty(result)) return result;
		temp = temp->nextBrotherAddress;
	}

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
	if(isEmpty(currentPath)) {printf("\nNULLL\n"); return;}
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

// delete menggunakan postorder travrsal
void massDelete(treeAddress * target){
	if(isEmpty(*target)) return;

	treeAddress temp = (*target)->sonAddress;	//kalo leaf, temp = NULL
	while(!isEmpty(temp)){
		treeAddress next = temp->nextBrotherAddress;	//temp bakal dihapus
		massDelete(&temp);
		temp = next;
	}
	deleteNode(target);

	return;
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

void deAlokasi (treeAddress * target){
	if(isEmpty(*target)) return;

	free(*target);
	(*target) = NULL;
}
