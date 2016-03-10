#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define ARRAY_SIZE 10000

pthread_mutex_t mutex;

int sum = 0;

void* sumfunc1()
{
	int i;
	for (i = 0; i < ARRAY_SIZE / 2; ++i)
	{
		//calculates sin and cos only once
		pthread_mutex_lock(&mutex);
		int temp_sum = sin(i) * sin(i) + cos(i) * cos(i);
		
		sum += temp_sum;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void* sumfunc2()
{
	int i;
	for (i = ARRAY_SIZE / 2; i < ARRAY_SIZE; ++i)
	{
		pthread_mutex_lock(&mutex);
		int temp_sum = sin(i) * sin(i) + cos(i) * cos(i);
		
		sum += temp_sum;
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main() 
{
	int mutexInitializationError = pthread_mutex_init(&mutex, NULL);
	if (mutexInitializationError)
	{
		printf("Mutex was not initialized!\n");
		return 0;
	}

	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, sumfunc1, NULL);
	pthread_create(&thread2, NULL, sumfunc1, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("%d \n", sum);

	pthread_mutex_destroy(&mutex);

	return 0;
}