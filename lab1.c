/*Miguel Lima Tavares
 *DRE:119161571
 *Disciplina: Computacao Concorrente
 *Prof: Silvana Rossetto
 *Laboratorio 1
*/
#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NVETOR 10000

int *vetor;
int *copia; //copia do vetor original para comparacao


//--------------------------------------------------------------

//incremente 1 ao vetor
void *incrementar (void *arg) {

    int id = * (int*) arg;

    //incrementa impares e pares separadamente na thread
    if (id == 1 || id == 2){
        for (int i = id; i < NVETOR; i += 2){
            vetor[i] += 1;         
        }    
    }
    pthread_exit(NULL);
}

//--------------------------------------------------------------

// Aloca espaco na memoria para matriz
void alocarMatrix() {

    int num;

    //Alocacao de um vetor
    vetor = (int*) malloc(NVETOR * sizeof(int*));
    copia = (int*) malloc(NVETOR * sizeof(int*));


    if (vetor == NULL) {
        printf ("Erro ao alocar memoria");
        return ;
    }

    // aloca memoria para item do vetor
    for (int i = 0; i < NVETOR; i++) {
  
        // inicializa matriz com numeros aleatorios
            for (int j = 0; j < NVETOR; j++)
                num = rand() % 10;
                vetor[i] = num;
                copia[i] = num; 
    }
    
}

//--------------------------------------------------------------

int main(void){

    pthread_t tid_sistema[1]; 

    int impar = 1;
    int par = 2;

    alocarMatrix();
    
    //incrementa o primeiro numero do vetor
    vetor[0] += 1;

    //threads para numeros impares
    if (pthread_create(&tid_sistema[0], NULL, incrementar, (void*) &impar)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
    //thread para numeros pares
    if (pthread_create(&tid_sistema[0], NULL, incrementar, (void*) &par)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }

    //--espera todas as threads terminarem
    for (int i = 0; i < 1; i++) {
        if (pthread_join(tid_sistema[i], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
    }
    

    //verifica se os valores finais estao corretos
    for (int i = 0; i < NVETOR; i++){   
        if (copia[i] + 1 != vetor[i]){
            printf("Falha ao verificar vetor\n");
            return 1;
        }
    }

    printf("Verificacao bem sucedida, vetor incrementado corretamente\n");
}
