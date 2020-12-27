#include <stdio.h>
#include<stdlib.h>
#include <time.h>

int contadorDeTrocas=0;
int contadorDeComparacoes=0;

int troca(int *vetor, int indiceElementoUm,int indiceElementoDois){
    int aux = vetor[indiceElementoUm];
    vetor[indiceElementoUm] = vetor[indiceElementoDois];
    vetor[indiceElementoDois] = aux;
    return *vetor;
}

int gerarValores(){
    return (rand()% 99999) *1;
}

int gerarVetorAleatorio(int *vetor, int inicio, int tamanho){
    if(inicio==tamanho){
        return *vetor;

    }
    else{
        vetor[inicio] = gerarValores();
        gerarVetorAleatorio(vetor, inicio+1, tamanho);
    }
}

int inverteVetor(int *vetor, int inicio, int tamanho){
    if(inicio==tamanho){
        return *vetor;
    }
    else{
        troca(vetor, inicio, tamanho-1);
        return inverteVetor(vetor, inicio+1, tamanho-1);
    }
}

//heapMax faz o maior elemento ir para a raiz do nosso vetor principal
void heapMax(int *vetor, int tamanho, int indiceInicial) {
    int indiceMaior = indiceInicial; // Initialize indiceMaior as root 
    int indiceFilhoEsquerda = 2*indiceInicial + 1;
    int indiceFilhoDireita = 2*indiceInicial + 2;
    if (indiceFilhoEsquerda < tamanho && vetor[indiceFilhoEsquerda]>vetor[indiceMaior]){
        indiceMaior = indiceFilhoEsquerda;
        contadorDeComparacoes++;
    }
  
    if (indiceFilhoDireita < tamanho && vetor[indiceFilhoDireita] > vetor[indiceMaior]){
        indiceMaior = indiceFilhoDireita;
        contadorDeComparacoes++;
    }

    if (indiceMaior != indiceInicial){ 
        troca(vetor, indiceInicial, indiceMaior);
        contadorDeTrocas++;
        heapMax(vetor, tamanho, indiceMaior);
    }
}

void constroiHeap(int *vetor, int tamanho, int i){
    if(i<0){
        return;
    }
    else{
        heapMax(vetor, tamanho, i);
        constroiHeap(vetor, tamanho, i-1);
    }
}

void ordena(int *vetor, int i){
    if(i<0){
        return;
    }
    else{
        troca(vetor, 0, i);
        contadorDeTrocas++;
        heapMax(vetor, i, 0);
        ordena(vetor, i-1);
    }
}

void heapSort(int *vetor, int tamanho) {
    //constroi a heap max
    // Build heap (revetorange vetoray) 
    int i=tamanho/2-1;
    constroiHeap(vetor, tamanho, i);
    i=tamanho-1;
    ordena(vetor, i);
}

void imprimeVetor(int *vetor, int inicio, int tamanho){
    if(inicio==tamanho){
        return;
    }
    else{
        printf("%d ", vetor[inicio]);
        imprimeVetor(vetor, inicio+1,tamanho);
    }
}
clock_t tempo[2];
double tempoTotal = 0;
double Tempo;

void vetorDesordenado(int *vetor, int inicio, int tamanho, int quantidade){
    if(inicio == quantidade){
        printf("***************DESORDENADO*******************");
        printf("\nQuantidade Media de Comparacoes: %d", contadorDeComparacoes/quantidade);
        printf("\nQuantidade Media de Trocas: %d", contadorDeTrocas/quantidade);
        printf("\nTempo Medio Gasto: %g ms.\n", tempoTotal/quantidade);
    }
    else{
        gerarVetorAleatorio(vetor, inicio, tamanho);
        tempo[0]= clock();
        heapSort(vetor, tamanho);
        tempo[1]= clock();
        Tempo = (tempo[1] - tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
        imprimeVetor(vetor, inicio, tamanho);
        printf("\n%lf\n", Tempo);
        tempoTotal = tempoTotal + Tempo;
        vetorDesordenado(vetor, inicio+1, tamanho, quantidade);
    }
}

void vetorOrdenado(int *vetor, int inicio, int tamanho){
    gerarVetorAleatorio(vetor, inicio, tamanho);
    heapSort(vetor, tamanho); //ordena o vetor
    
    tempoTotal=0;
    contadorDeComparacoes=0;
    contadorDeTrocas=0;
    Tempo=0;
    tempo[0] = clock();
    heapSort(vetor, tamanho); //aplicado no vetor ja ordenado
    //imprimeVetor(vetor, inicio, tamanho);
    tempo[1] = clock();
    Tempo = (tempo[1] - tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("\n");
    printf("**************ORDENADO********************");
    printf("\nQuantidade de Comparacoes: %d", contadorDeComparacoes);
    printf("\nQuantidade de Trocas: %d", contadorDeTrocas);
    printf("\nTempo Gasto: %g ms.\n", Tempo);
}

void vetorInversamenteOrdenado(int *vetor, int inicio, int tamanho){    
    gerarVetorAleatorio(vetor, inicio, tamanho);
    heapSort(vetor, tamanho);
    inverteVetor(vetor, inicio, tamanho);
    //imprimeVetor(vetor, inicio, tamanho);
    printf("\n");
    Tempo=0;
    contadorDeComparacoes=0;
    contadorDeTrocas=0;
    tempo[0] = clock();
    heapSort(vetor, tamanho);
    tempo[1] = clock();
    Tempo = (tempo[1] - tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
    tempoTotal = tempoTotal+Tempo;
    printf("*************INVERSAMENTE ORDENADO*********************");
    printf("\nQuantidade de Comparacoes: %d", contadorDeComparacoes);
    printf("\nQuantidade de Trocas: %d", contadorDeTrocas);
    printf("\nTempo Gasto: %g ms.\n", tempoTotal);
}

int main() {
    srand((unsigned) time(NULL));
    int vetor[1000], tamanho=1000;
    int inicio=0, quantidade=40;
    vetorDesordenado(vetor, inicio, tamanho, quantidade);
    vetorOrdenado(vetor, inicio, tamanho);
    vetorInversamenteOrdenado(vetor, inicio, tamanho);
    printf("\n");
}