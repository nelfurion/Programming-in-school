#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* test(void* p)
{
	//typecasting - reads the same piece of memory - the same memory, but interprets it in a different way
	int id = (int)p;
	//otherwise we return a pointer to a local variable
	int* result = malloc(sizeof(int));
	printf("hello from thread %d\n", id);

	result = id * id;
	return (void*)result;
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int i;

	for (i = 0; i < NUM_THREADS; ++i)
	{
		if(pthread_create(&threads[i], NULL, test, (void*)i)) 
		{
			perror("error in pthread_create...");
		}
	}
	
	//the main thread may finish before all the threads have
	//so we join them with it
	for (i = 0; i < NUM_THREADS; ++i)
	{
		void* result;
		pthread_join(threads[i], (void**)&result);
		printf("Thread %d returned %d\n",i, (int) result);
	}

	return 0;
}