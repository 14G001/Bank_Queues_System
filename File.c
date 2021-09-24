#include <stdio.h>
#include <stdlib.h>

#include "File.h"


void close(FILE* file)
{
	fclose(file);
	free(file);
}
