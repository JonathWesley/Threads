#include <stdio.h>
#include <omp.h>

#define TAM 800

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
            while(nItens < TAM){
                printf("Number of itens: %d - %d\n", nItens, omp_get_thread_num());
            }
        }
        

        while(nItens < TAM){
            #pragma omp critical
            {
                weight[nItens ] = rand() % 10 + 1;
                nItens += 1;
                printf("Thread: %d\n", omp_get_thread_num());
            }
        }
        
	}

    printf("Number of itens: %d\n", nItens);
    printf("Peso total: %d\n", sum(weight));

    return 0;
}