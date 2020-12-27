#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int contadorDeTrocas=0;
int contadorDeComparacoes=0;

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

void imprimeVetor(int *vetor, int inicio, int tamanho){
	if(inicio==tamanho){
		return;
	}
	else{
		printf("%d ", vetor[inicio]);
		imprimeVetor(vetor, inicio+1,tamanho);
	}
}

int troca(int *vetor, int indiceElementoUm,int indiceElementoDois){
	int aux = vetor[indiceElementoUm];
	vetor[indiceElementoUm] = vetor[indiceElementoDois];
	vetor[indiceElementoDois] = aux;
	return *vetor;
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

void copiaElementos(int *vetor, int inicio, int final, int indiceAux, int *vetorAux){
	if(indiceAux == final-inicio+1){
		return;
	}
	else{
		vetor[inicio+indiceAux]=vetorAux[indiceAux];
		copiaElementos(vetor, inicio, final, indiceAux+1,vetorAux);
	}
}

void intercala(int *vetor, int inicio, int meio, int j, int final, int indiceAux, int *vetorAux){
	contadorDeComparacoes++;
	if(inicio<=meio && (j> final || vetor[inicio] < vetor[j])){
		contadorDeTrocas++;
		vetorAux[indiceAux] = vetor[inicio];
		intercala(vetor, inicio+1, meio, j, final, indiceAux+1, vetorAux);
	}

	else{
		if(j<=final){
			vetorAux[indiceAux]=vetor[j];
			intercala(vetor, inicio, meio, j+1, final, indiceAux+1, vetorAux);
		}
	}
}


void merge(int *vetor, int indiceInicio, int indiceFinal, int *vetorAux){
	int meio=(indiceInicio+indiceFinal)/2;

	if(indiceInicio<indiceFinal){
		merge(vetor, indiceInicio, meio, vetorAux);
		merge(vetor, meio+1, indiceFinal, vetorAux);

		intercala(vetor, indiceInicio, meio, meio+1, indiceFinal, 0, vetorAux);

		copiaElementos(vetor, indiceInicio, indiceFinal, 0, vetorAux);
	}
}

void mergeSort(int *vetor, int tamanho) {
    int *vetorAux = malloc(sizeof(int) * 1000);
    merge(vetor, 0, tamanho, aux);
    free(vetorAux);
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
		mergeSort(vetor, tamanho);
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
	mergeSort(vetor, tamanho-1); //ordena o vetor
	
	tempoTotal=0;
	contadorDeComparacoes=0;
	contadorDeTrocas=0;
	Tempo=0;
	tempo[0] = clock();
	mergeSort(vetor, tamanho-1); //aplicado no vetor ja ordenado
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

	mergeSort(vetor, tamanho-1);
	inverteVetor(vetor, inicio, tamanho);
	//imprimeVetor(vetor, inicio, tamanho);
	printf("\n");
	Tempo=0;
	contadorDeComparacoes=0;
	contadorDeTrocas=0;
	tempo[0] = clock();
	mergeSort(vetor, tamanho);
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
    int inicio=0, tamanho=1000;
    int vetor[1000], quantidade =40;
    vetorDesordenado(vetor, inicio, tamanho, quantidade);
    vetorOrdenado(vetor, inicio, tamanho);
    vetorInversamenteOrdenado(vetor, inicio, tamanho);

}