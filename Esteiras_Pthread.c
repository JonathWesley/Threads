#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100

pthread_mutex_t lock;

struct Products{
	int nItens;
	int weight[TAM];
};

/* this function is run by the threads */
void *inc(void *arguments){
    /* increment x to 100 */
    struct Products *p = (struct Products *)arguments;

    while(p->nItens < TAM){
		pthread_mutex_lock(&lock);
		if(p->nItens < TAM){
			p->weight[p->nItens ] = rand() % 10 + 1;
			p->nItens += 1;
		}
		
		//printf("%lu - %d\n", pthread_self(), p->nItens);
		pthread_mutex_unlock(&lock);

		//delay(10);
	}
	
    /* the function must return something - NULL will do */
    return NULL;
}

int sum(int array[]){
	int sum = 0, i;
	for(i = 0; i<TAM; i++){
		sum += array[i];
	}
	return sum;
}

int main(){
	srand(time(NULL));

	clock_t start, finish;
	double time;

	start = clock();

    struct Products p;
	
	//char stop = 's';
	int i = 0;
	while(i < 5){
		if(pthread_mutex_init(&lock, NULL) != 0){
			printf("\nMutex init failed.\n");
			return 1;
		}

		p.nItens = 0;

		/* this variable is our reference to the second thread */
		pthread_t thread_2, thread_3, thread_4;

		/* create a second thread which executes inc_x(&x) */
		if(pthread_create(&thread_2, NULL, inc, &p)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}else
			printf("Thread 2 Criada\n");
		/* create a third thread which executes inc_x(&x) */
		if(pthread_create(&thread_3, NULL, inc, &p)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}else
			printf("Thread 3 Criada\n");
		/* create a fourth thread which executes inc_x(&x) */
		if(pthread_create(&thread_4, NULL, inc, &p)) {
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}else
			printf("Thread 4 Criada\n");

		/* increment y to 100 in the first thread */
		while(p.nItens < TAM){
			printf("Number of Itens: %d\n", p.nItens);
		}

		/* wait for the second thread to finish */
		if(pthread_join(thread_2, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
		if(pthread_join(thread_3, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
		if(pthread_join(thread_4, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}

		/* show the results - x is now 100 thanks to the second thread */
		printf("Number of Itens: %d\n", p.nItens);
		printf("Peso total: %d\n", sum(p.weight));

		pthread_mutex_destroy(&lock);

		//scanf("%s", &stop);
		i++;
	}

	finish = clock();

	time = ((double) (finish - start)) / CLOCKS_PER_SEC;

	printf("Tempo: %f\n", time);

    return 0;
}
