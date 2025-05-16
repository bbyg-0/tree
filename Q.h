#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "treeNode.h"

typedef struct queue *qAddress;
typedef struct queue{
	treeAddress x;
	qAddress next;
}Q;

void qCreateMemory(qAddress *target);

void isiQ(qAddress *node, treeAddress target);

void insertQ(qAddress *head, qAddress *target);

treeAddress deQ(qAddress *head);

void deAlokasiQ (qAddress *target);

#endif
