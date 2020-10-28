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
		p.nItens = 0;
		thread_complete = 0;

		start = clock();

		/* increment y to 100 in the first thread */
		while(p.nItens < TAM){
			printf("Number of Itens: %d\n", p.nItens);
            if(simulaEntrada()){
				p.weight[p.nItens ] = rand() % 10 + 1;
				p.nItens += 1;
			}
		}

		finish = clock();

		timeThreads = ((double) (finish - start)) / CLOCKS_PER_SEC;

		start = clock();
		
		pesoTotal += sum(p.weight);
		
		/* show the results - x is now 100 thanks to the second thread */
		printf("Number of Itens: %d\n", p.nItens);
		printf("Peso total: %d\n", pesoTotal);

		finish = clock();

		time = ((double) (finish - start)) / CLOCKS_PER_SEC;

		printf("Tempo threads: %f\n", timeThreads);
		printf("Tempo soma: %f\n", time);

		i++;
	}

	finishTotal = clock();

	timeTotal = ((double) (finishTotal - startTotal)) / CLOCKS_PER_SEC;

	printf("Tempo total: %f\n", timeTotal);

    return 0;
}
