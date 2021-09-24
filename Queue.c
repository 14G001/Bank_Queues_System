#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"


void create(QUEUE* que)
{
	que->head = NULL;
	que->tail = NULL;
	que->numberOfPendingShifts = 0;
	return;
}


void queue(CLIENT value, QUEUE* que)
{
	Q_NODE* newQue = (Q_NODE*)malloc(sizeof(Q_NODE));
	newQue->value = value;
	newQue->next = NULL;
	if (que->head == NULL) {
		que->head = newQue;
	} else {
		que->tail->next = newQue;
	}
	que->tail = newQue;
	return;
}


void priorityQueue(CLIENT value, QUEUE* que)
{
	Q_NODE* newQue = (Q_NODE*)malloc(sizeof(Q_NODE));
	newQue->value = value;
	newQue->next = que->head;
	que->head = newQue;
	return;
}


CLIENT dequeue(QUEUE* que)
{
	CLIENT value = que->head->value;
	Q_NODE* recQue = que->head;
	que->head = que->head->next;
	free(recQue);
	return value;
}


void attendSpecially(Q_NODE* pregnantWoman, QUEUE* queue)
{
	Q_NODE* auxNode = queue->head;

	if (auxNode == pregnantWoman) {
		dequeue(queue);
	} else {
		
		while (auxNode->next != pregnantWoman) {
			auxNode = auxNode->next;
		}

		Q_NODE* recNode = auxNode->next;
		auxNode->next = auxNode->next->next;
		free(recNode);
	}
	return;
}


Q_NODE* isThereAPregnantWoman(QUEUE* queue)
{
	Q_NODE* pregnantWoman = NULL;
	Q_NODE* auxNode = queue->head;
	
	while (auxNode != NULL) {
		if (auxNode->value.type == 'E') {
			pregnantWoman = auxNode;
		}
		// Although it has found one, the "while" keeps in to attend the first woman that arrived at the bank (in order of arriving).
		auxNode = auxNode->next;
	}

	return pregnantWoman;
}


bool isEmpty(QUEUE que)
{
	if (que.head == NULL) {
		return true;
	}
	return false;
}


void freeQueue(QUEUE* que)
{
	while (que->head != NULL) {
		dequeue(que);
	}
	return;
}


void createPtr(QUEUE** que)
{
	*que = (QUEUE*)malloc(sizeof(QUEUE));
	(*que)->head = NULL;
	(*que)->tail = NULL;
	return;
}


void freeQueuePtr(QUEUE** que)
{
	while ((*que)->head != NULL) {
		dequeue(*que);
	}
	free(*que);
	return;
}
