#pragma once


typedef struct CLIENT {
	char name[41];
	int id;
	bool operation; // true -> Put away money | false -> Withdraw money
	float amountMoney;
	char type; // 'M' -> Pregnant & Premium 'E' -> Pregnant | 'C' -> Simple client | 'P' -> Premium client
	int number;
} CLIENT;


typedef struct Q_NODE {
	CLIENT value;
	struct Q_NODE* next;
} Q_NODE;


typedef struct QUEUE {
	short int numberOfPendingShifts;
	Q_NODE* head;
	Q_NODE* tail;
} QUEUE;


void create(QUEUE* que);

void queue(CLIENT value, QUEUE* que);

void priorityQueue(CLIENT value, QUEUE* que);

CLIENT dequeue(QUEUE* que);

void attendSpecially(Q_NODE* pregnantWoman, QUEUE* queue);

Q_NODE* isThereAPregnantWoman(QUEUE* queue);

bool isEmpty(QUEUE que);

void freeQueue(QUEUE* que);

void createPtr(QUEUE** que);

void freeQueuePtr(QUEUE** que);
