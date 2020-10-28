#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define TAM 1500

pthread_mutex_t lock;
int thread_complete;

struct Products{
	int nItens;
	int weight[TAM];
};

int simulaEntrada(){
	int r = rand()%10;
	if(r == 0)
		return 1;
	else
		return 0; 
}

void *inc(void *arguments){
    struct Products *p = (struct Products *)arguments;

    while(p->nItens < TAM){
		if(simulaEntrada()){
			pthread_mutex_lock(&lock);
			if(p->nItens < TAM){
				p->weight[p->nItens ] = rand() % 10 + 1;
				p->nItens += 1;
			}
			//printf("Thread %lu\n",  pthread_self());
			pthread_mutex_unlock(&lock);
		}
	}
	
	thread_complete = 1;

    return NULL;
}

/*
int kbhit(void){
	struct termios oldt, newt;
	int ch;
	int oldf;
	
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	
	ch = getchar();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	
	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	
	return 0;
}

void *inc2(void *arguments){
    struct Products *p = (struct Products *)arguments;

    while(p->nItens < TAM){
		if(kbhit()){
			if(getchar() == 'q'){
				pthread_mutex_lock(&lock);
				p->weight[p->nItens ] = rand() % 10 + 1;
				p->nItens += 1;
				pthread_mutex_unlock(&lock);
				printf("Thread %lu: %d\n",  pthread_self(), p->nItens);
			}
		}
	}
	
	thread_complete = 1;

    return NULL;
}

void *inc3(void *arguments){
    struct Products *p = (struct Products *)arguments;

    while(p->nItens < TAM){
		if(kbhit()){
			if(getchar() == 'w'){
				pthread_mutex_lock(&lock);
				p->weight[p->nItens ] = rand() % 10 + 1;
				p->nItens += 1;
				pthread_mutex_unlock(&lock);
				printf("Thread %lu: %d\n",  pthread_self(), p->nItens);
			}
		}
	}
	
	thread_complete = 1;

    return NULL;
}

void *inc4(void *arguments){
    struct Products *p = (struct Products *)arguments;

    while(p->nItens < TAM){
		if(kbhit()){
			if(getchar() == 'e'){
				pthread_mutex_lock(&lock);
				p->weight[p->nItens ] = rand() % 10 + 1;
				p->nItens += 1;
				pthread_mutex_unlock(&lock);
				//printf("Thread %lu: %d\n",  pthread_self(), p->nItens);
			}
		}
	}
	
	thread_complete = 1;

    return NULL;
}
*/

int sum(int array[]){
	int sum = 0, i;
	for(i = 0; i<TAM; i++){
		sum += array[i];
	}
	return sum;
}

int main(){
	srand(time(NULL));

	clock_t start, finish, startTotal, finishTotal;
	double time, timeThreads, timeTotal;

    struct Products p;
	int pesoTotal = 0;
	
	startTotal = clock();
	//char stop = 's';
	int i = 0;
	while(i < 1){
		if(pthread_mutex_init(&lock, NULL) != 0){
			printf("\nMutex init failed.\n");
			return 1;
		}

		p.nItens = 0;
		thread_complete = 0;

		start = clock();

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
		while(!thread_complete){
			printf("Number of Itens: %d\n", p.nItens);
		}

		/* wait for the second thread to finish */
		if(pthread_join(thread_2, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}else
			printf("Thread 2 foi destruida.\n");
		if(pthread_join(thread_3, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}else
			printf("Thread 3 foi destruida.\n");
		if(pthread_join(thread_4, NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}else
			printf("Thread 4 foi destruida.\n");

		finish = clock();

		timeThreads = ((double) (finish - start)) / CLOCKS_PER_SEC;

		start = clock();
		
		pesoTotal += sum(p.weight);
		
		/* show the results - x is now 100 thanks to the second thread */
		printf("Number of Itens: %d\n", p.nItens);
		printf("Peso total: %d\n", pesoTotal);
		

		pthread_mutex_destroy(&lock);

		finish = clock();

		time = ((double) (finish - start)) / CLOCKS_PER_SEC;

		printf("Tempo threads: %f\n", timeThreads);
		printf("Tempo soma: %f\n", time);

		//scanf("%s", &stop);
		i++;
	}
	finishTotal = clock();

	timeTotal = ((double) (finishTotal - startTotal)) / CLOCKS_PER_SEC;

	printf("Tempo total: %f\n", timeTotal);

    return 0;
}
