#include <stdio.h>
#include <omp.h>

#define TAM 800

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

int main(int argc, char** argv){
    srand(time(NULL));

    int nItens = 0, weight[TAM];

    #pragma omp parallel shared(nItens, weight) num_threads(4) 
	{
        #pragma omp single nowait
        {
            printf("Criei Thread: %d\n", omp_get_thread_num());
            while(nItens < TAM){
                printf("Number of itens: %d - %d\n", nItens, omp_get_thread_num());
            }
        }

        printf("Criei Thread: %d\n", omp_get_thread_num());
        while(nItens < TAM){
            if(simulaEntrada()){
                #pragma omp critical
                {   
                    if(nItens < TAM){
                        weight[nItens] = rand() % 10 + 1;
                        nItens += 1;
                        printf("Thread: %d\n", omp_get_thread_num());
                    }
                }
            }
        }
	}

    printf("Number of itens: %d\n", nItens);
    printf("Peso total: %d\n", sum(weight));

    return 0;
}