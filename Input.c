#include <stdio.h>
#include <stdlib.h>

#include "Input.h"


void cleanString(char input[], int size)
{
    int i = 0;
    for (i; i < size && input[i] != '\n' && input[i] != '\0'; i++);

    if (input[i] == '\n') {
        input[i] = '\0';
        i++;
        while (i < size) {
            if (input[i] == '\0') {
                input[i] = 'a';
            }
            i++;
        }
    }
    return;
}


void inputString(char input[], int size)
{
    fgets(input, size, stdin);

    int i = 0;
    for (i; i < size && input[i] != '\n' && input[i] != '\0'; i++);

    if (input[i] == '\n') {
        input[i] = '\0';
        i++;
        while (i < size) {
            if (input[i] == '\0') {
                input[i] = 'a';
            }
            i++;
        }
    }
    return;
}


int inputInt(int size)
{
    char input[size];
    fgets(input, sizeof(input), stdin);
    return atoi(input);
}


float inputFloat(int size)
{
    char input[size];
    fgets(input, sizeof(input), stdin);
    return atof(input);
}


char inputChar(int size)
{
    char input[size];
    fgets(input, sizeof(input), stdin);
    return input[0];
}
