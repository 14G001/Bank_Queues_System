#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Input.h"
#include "Queue.h"
#include "File.h"
#include "main_functions.h"


int main()
{
	QUEUE que_std; create(&que_std);
	QUEUE que_pre; create(&que_pre);
	bool nextQue = false; // true -> The next queue where the client will be attended will be the standard one.
						  // false -> The next queue where the client will be attended will be the premium one.
	int clientNumber = 1;

	char option = '1';

	while (option != '5') {
		printMenu(&option);

		if (option == '1') {
			newClient(&que_std, &que_pre, &clientNumber);
		} else if (option == '2') {
			attendClient(&que_std, &que_pre, &nextQue);
		} else if (option == '3') {
			printQueues(que_std, que_pre);
		} else if (option == '4') {
			showSpecificClientInfo(que_std, que_pre);
		}
	}

	freeQueue(&que_std);
	freeQueue(&que_pre);
	return 0;
}
