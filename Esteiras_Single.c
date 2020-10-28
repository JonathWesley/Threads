#include <stdio.h>
#include <time.h>

#define TAM 1500

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

    int nItens;
	int weight[TAM];
	int pesoTotal = 0;
	
	startTotal = clock();

	int i = 0;
	while(i < 1){
		nItens = 0;

		start = clock();

		while(nItens < TAM){
			printf("Number of Itens: %d\n", nItens);
            if(simulaEntrada()){
				weight[nItens ] = rand() % 10 + 1;
				nItens += 1;
			}
		}

		finish = clock();

		timeThreads = ((double) (finish - start)) / CLOCKS_PER_SEC;

		start = clock();
		
		pesoTotal += sum(weight);
		
		printf("Number of Itens: %d\n", nItens);
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
