#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "../processors/filters.h"


void* input_thread(void* arg,int *running);
