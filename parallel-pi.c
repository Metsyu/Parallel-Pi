#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Global variables
#define NUM_THREADS 4
int points = 0;
pthread_mutex_t mutex;

void * runner()
{
	//Lock mutex
	pthread_mutex_lock(&mutex);
	
	for(int i = 0; i < 2500000; i++)
	{
		//Generate a point (x,y)
		float x = 2.0 * ((float)rand() / ((float)RAND_MAX + 1.0)) - 1.0;
		float y = 2.0 * ((float)rand() / ((float)RAND_MAX + 1.0)) - 1.0;
		
		//If (x,y) fall in the circle, iterate points
		if(sqrt((x * x) + (y * y)) < 1.0 && sqrt((x * x) + (y * y)) > -1.0)
			points++;
	}
	
	//Unlock mutex
	pthread_mutex_unlock(&mutex);
	
	pthread_exit(NULL);
}

int main()
{
	//Seed rand()
	srand(time(NULL));
	pthread_t threads[NUM_THREADS];
	
	//Initialize mutex
	pthread_mutex_init(&mutex, NULL);

	//Create and deploy pthreads
	int rc;
	long t;
	for(t = 0; t < NUM_THREADS; t++)
	{
		printf("In main: creating thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, runner, NULL);
		
		if (rc)
		{
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	
	//Join pthreads back to main
	for(t = 0; t < NUM_THREADS; t++)
	{
		pthread_join(threads[t], NULL);
	}
	
	//Destroy mutex
	pthread_mutex_destroy(&mutex);
	
	//Calculate and print estimate
	float estimate = 4.0 * (float)points/10000000.0;
	printf("The estimate for pi is %f\n", estimate);
	
	return 0;
}
