#include <math.h>
#include <stdio.h>
#include <pthread.h>

#define THREADS_COUNT 4
#define NUMBERS_TO_CHECK 25000000
#define STEP NUMBERS_TO_CHECK

void* isTrigonometryRuleCorrect(void* arg) {
	int argument = (int)arg;
	int start_number = malloc(sizeof(int));
	start_number = argument;

	int i, error = 0;
	for (i = start_number; i <= start_number + NUMBERS_TO_CHECK; ++i)
	{
		double a = cos(i) * cos(i) + sin(i) * sin(i);
		if (a > 1.0005 || a < 0.9995) {
			error = 1;
			break;
		}
	}

	return error;
}

int main() {
	pthread_t threads[THREADS_COUNT];
	int i,
		start_number = 0;

	for (i = 0; i < THREADS_COUNT; ++i)
	{
		if(pthread_create(&threads[i], NULL, isTrigonometryRuleCorrect, (void*)start_number)) 
		{
			perror("error in pthread_create...");
		}

		start_number += STEP;
	}

	for (i = 0; i < THREADS_COUNT; ++i)
	{
		void* result;
		pthread_join(threads[i], (void**)&result);
		if((int)result == 1) {
			printf("The trigonometry rule is not correct!\n");
			return 0;
		}
	}

	printf("The trigonometry rule is correct!\n");
	return 0;
}