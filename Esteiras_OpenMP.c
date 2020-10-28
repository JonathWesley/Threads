#include <stdio.h>
#include <omp.h>
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

int main(int argc, char** argv){
    srand(time(NULL));

    clock_t start, finish;
	double time;

    int nItens, weight[TAM], pesoTotal;

    int i = 0;
    while(i < 1){
        nItens = 0;
        pesoTotal = 0;

        #pragma omp parallel shared(nItens, weight) num_threads(4) 
        {
            #pragma omp single nowait
            {
                printf("Thread %d criada.\n", omp_get_thread_num());
                while(nItens < TAM){
                    printf("Number of itens: %d\n", nItens);
                }
            }

            //para nao printar que ta criando a thread do lcd
            if(nItens < TAM){
                printf("Thread %d criada.\n", omp_get_thread_num());
            }
            while(nItens < TAM){
                if(simulaEntrada()){
                    #pragma omp critical
                    {   
                        if(nItens < TAM){
                            weight[nItens] = rand() % 10 + 1;
                            nItens += 1;
                            //printf("Thread: %d\n", omp_get_thread_num());
                        }
                    }
                }
            }

            printf("Thread %d destruida.\n", omp_get_thread_num());
        }

        start = clock();

        pesoTotal += sum(weight);

        printf("Number of itens: %d\n", nItens);
        printf("Peso total: %d\n", pesoTotal);

        finish = clock();

        time = ((double) (finish - start)) / CLOCKS_PER_SEC;

        printf("Tempo: %f\n", time);

        i++;
    }
    

    return 0;
}