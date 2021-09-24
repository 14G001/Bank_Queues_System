#include "Queue.h"


void printMenu(char* option);


void print(CLIENT Client);


CLIENT getClient(FILE* file, int* clientNumber);


void newClient(QUEUE* que_std, QUEUE* que_pre, int* clientNumber);


void attendClient(QUEUE* que_std, QUEUE* que_pre, bool* nextQue);


void printQueues(QUEUE que_std, QUEUE que_pre);


Q_NODE* searchClient(QUEUE queue, int posQueue);


void showSpecificClientInfo(QUEUE que_std, QUEUE que_pre);
