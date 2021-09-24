#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Input.h"
#include "Queue.h"
#include "File.h"
#include "main_functions.h"


void printMenu(char* option)
{
	printf("Options:\n\n");
	printf("1) Add a new client.\n");
	printf("2) Attend a client.\n");
	printf("3) View queues status.\n");
	printf("4) View specific client info.\n");
	printf("5) Exit.\n\n\n\n");
	*option = inputChar(3);
	return;
}


void print(CLIENT Client)
{
	printf("Client data:\n\n");
	printf("Name: %s\n", Client.name);
	printf("ID: %i\n", Client.id);
	printf("Operation: %i\n", Client.operation); // true -> Guardar | false -> Retirar
	printf("Amount of money: %f$\n", Client.amountMoney);
	printf("Type: %c\n", Client.type); // 'M' -> Embarazada y Premium 'E' -> Embarazada | 'C' -> Client Comun | 'P' -> Client Premium
	printf("Number: %i\n\n\n\n", Client.number);
	return;
}


CLIENT getClient(FILE* file, int* clientNumber)
{
	CLIENT Client;
	Client.number = *clientNumber;
	char textLine[51];
	fgets(textLine, sizeof(textLine), file);
	cleanString(textLine, sizeof(textLine));
	
	/* FORMAT:
		Name (George Emmerson)\n
		id (44392883)\n
		operation (1 o 0)\n
		Amount of money (32423.333)\n
		type (C, P, E o M)\n
	*/
	
	char* nextToken;
	strncpy(Client.name, strtok_s(textLine, "", &nextToken), sizeof(Client.name));
	fgets(textLine, sizeof(textLine), file);
	Client.id = atoi(strtok_s(textLine, "", &nextToken));
	fgets(textLine, sizeof(textLine), file); 
	Client.operation = atoi(strtok_s(textLine, "", &nextToken)); 
	fgets(textLine, sizeof(textLine), file); 
	Client.amountMoney = atof(strtok_s(textLine, "", &nextToken));
	fgets(textLine, sizeof(textLine), file);
	Client.type = textLine[0];
	return Client;
}


void newClient(QUEUE* que_std, QUEUE* que_pre, int* clientNumber)
{
	FILE* fileInput;
	fopen_s(&fileInput, "Client Input.txt", "r");
	if (fileInput == NULL) {
		printf("Couldn't find the data input file.\n\n");
		fopen_s(&fileInput, "Client Input.txt", "w");
	} else {

		if (*clientNumber > 800000) { // (As if the system was permanently on).
			*clientNumber = 0;
		}

		CLIENT Client = getClient(fileInput, clientNumber);
		*clientNumber += 1;

		if (Client.type == 'C') {
			queue(Client, que_std);
			que_std->numberOfPendingShifts++;
		} else if (Client.type == 'P') {
			queue(Client, que_pre);
			que_pre->numberOfPendingShifts++;
		} else if (Client.type == 'E') {
			priorityQueue(Client, que_std);
			que_pre->numberOfPendingShifts++;
		} else { // Client type is 'M' (Max priority)
			Client.type = 'E';
			priorityQueue(Client, que_pre);
			que_pre->numberOfPendingShifts++;
		}

	}

	close(fileInput);
	return;
}


void attendClient(QUEUE* que_std, QUEUE* que_pre, bool* nextQue)
{
	Q_NODE* pregnantWoman = isThereAPregnantWoman(que_pre);

	if (pregnantWoman != NULL) {

		attendSpecially(pregnantWoman, que_pre);
		que_pre->numberOfPendingShifts--;

	} else {

		pregnantWoman = isThereAPregnantWoman(que_std);

		if (pregnantWoman != NULL) {
			attendSpecially(pregnantWoman, que_std);
			que_std->numberOfPendingShifts--;
		} else if (que_pre->numberOfPendingShifts > 2) {
			dequeue(que_pre);
			que_pre->numberOfPendingShifts--;
			*nextQue = true;
		} else if ((*nextQue || isEmpty(*que_pre)) && !isEmpty(*que_std)) {
			dequeue(que_std);
			que_std->numberOfPendingShifts--;
			*nextQue = false;
		} else if (!isEmpty(*que_pre)) {
			dequeue(que_pre);
			que_pre->numberOfPendingShifts--;
			*nextQue = true;
		}
	}
	
	return;
}


void printQueues(QUEUE que_std, QUEUE que_pre)
{
	int i = 1;

	printf("Standard\tPremium\n");
	while (!isEmpty(que_std) && !isEmpty(que_pre)) {
		printf("%i %c\t\t%c\n", i, que_std.head->value.type, que_pre.head->value.type);
		que_std.head = que_std.head->next;
		que_pre.head = que_pre.head->next;
		i++;
	}

	while (!isEmpty(que_std)) {
		printf("%i %c\n", i, que_std.head->value.type);
		que_std.head = que_std.head->next;
		i++;
	}

	while (!isEmpty(que_pre)) {
		printf("%i\t\t%c\n", i, que_pre.head->value.type);
		que_pre.head = que_pre.head->next;
		i++;
	}

	printf("\n\n\n\n\n\n");

	return;
}


Q_NODE* searchClient(QUEUE queue, int posQueue)
{
	for (int i = 0; i < posQueue && queue.head != NULL; i++) {
		queue.head = queue.head->next;
	}
	return queue.head;
}


void showSpecificClientInfo(QUEUE que_std, QUEUE que_pre)
{
	printf("\n\n\nEnter in which one of the queues the client is ('C' Common or 'P' Premium): ");
	char que = inputChar(3);
	printf("Enter the position where the client is: ");
	int posQueue = inputInt(7);

	printf("\n\n\n\n");

	Q_NODE* ptrClient;
	if (que == 'C' || que == 'c') {
		ptrClient = searchClient(que_std, posQueue - 1);
	} else if (que == 'P' || que == 'p') {
		ptrClient = searchClient(que_pre, posQueue - 1);
	} else {
		printf("The data entered is not valid.\n\n\n\n");
		return;
	}
	
	if (ptrClient != NULL) {
		print(ptrClient->value);
	} else {
		printf("Sorry, we couldn't find a client in that position.");
	}
	return;
}
