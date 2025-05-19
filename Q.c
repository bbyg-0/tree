#include "Q.h"

#include <stdio.h>
#include <stdlib.h>

void qCreateMemory(qAddress *target){
	(*target) = (qAddress)malloc(sizeof(Q));

	if(isEmpty(*target)){printf("\nGAGAL MENGALOKASIKAN MEMORI\n"); return;}

	(*target)->x = NULL;
	(*target)->next = NULL;
}

void isiQ (qAddress *node, treeAddress target){
	if(isEmpty(*node)) return;

	(*node)->x = (target);
}

void insertQ (qAddress *head, qAddress *target){
	if(isEmpty(*head)){*head = *target; return;}

	(*target)->next = (*head);
	(*head) = (*target);
}

treeAddress deQ (qAddress *head){
	if(isEmpty(*head)) return NULL;
	if(isEmpty((*head)->next)){
		treeAddress result = (*head)->x;
		deAlokasiQ(head);
		return result;
	}
	qAddress temp = (*head);
	while(!isEmpty((*head)->next->next)){
		(*head) = (*head)->next;
	}
	treeAddress result = (*head)->next->x;
	deAlokasiQ(&((*head)->next));
	

	(*head) = temp;
	return result;
}

void deAlokasiQ (qAddress *target){
	if(isEmpty(*target))return;

	(*target)->x = NULL;
	(*target)->next = NULL;

	free(*target);
	(*target)= NULL;
}
