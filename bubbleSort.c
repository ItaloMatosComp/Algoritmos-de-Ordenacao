/*
********************ITALO DE MATOS SALDANHA***************
********************ENGENHARIA DA COMPUTACAO***************
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int contadorDeTrocas=0;
int contadorDeComparacoes=0;

int troca(int *vetor, int indiceElementoUm,int indiceElementoDois){
	int aux = vetor[indiceElementoUm];
	vetor[indiceElementoUm] = vetor[indiceElementoDois];
	vetor[indiceElementoDois] = aux;
	return *vetor;
}

int comparaElementos(int elementoDireita, int elementoEsquerda){
	if(elementoDireita > elementoEsquerda){
		return 1;
	}
	else{
		return 0;
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

int bubble(int *vetor, int indiceElemento, int tamanhoVetor){

	if(indiceElemento==tamanhoVetor || (contadorDeComparacoes==tamanhoVetor+1 && contadorDeTrocas==0)){
		return *vetor;
	}

	else{
		contadorDeComparacoes++;

		if(comparaElementos(vetor[indiceElemento], vetor[indiceElemento+1]) == 1){
			troca(vetor, indiceElemento, indiceElemento+1);
			contadorDeTrocas++;
			return bubble(vetor, indiceElemento+1, tamanhoVetor);
		}

		else{
			return bubble(vetor, indiceElemento+1, tamanhoVetor);
		}
	}
}

int bubbleSort(int *vetor, int indiceElemento, int tamanhoVetor, int contador){
	if(contador==tamanhoVetor){
		return *vetor;
	}

	else{
		bubble(vetor, indiceElemento, tamanhoVetor);
		bubbleSort(vetor, indiceElemento, tamanhoVetor, contador+1);
	}
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
		bubbleSort(vetor, 0, tamanho -1, 0);
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
	bubbleSort(vetor, 0, tamanho-1, 0); //ordena o vetor
	
	tempoTotal=0;
	contadorDeComparacoes=0;
	contadorDeTrocas=0;
	Tempo=0;
	tempo[0] = clock();
	bubbleSort(vetor, 0, tamanho-1, 0); //aplicado no vetor ja ordenado
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

	bubbleSort(vetor, 0, tamanho-1, 0);
	inverteVetor(vetor, inicio, tamanho);
	//imprimeVetor(vetor, inicio, tamanho);
	printf("\n");
	Tempo=0;
	contadorDeComparacoes=0;
	contadorDeTrocas=0;
	tempo[0] = clock();
	bubbleSort(vetor, inicio, tamanho, 0);
	tempo[1] = clock();
	Tempo = (tempo[1] - tempo[0]) * 1000.0 / CLOCKS_PER_SEC;
	tempoTotal = tempoTotal+Tempo;
	printf("*************INVERSAMENTE ORDENADO*********************");
	printf("\nQuantidade de Comparacoes: %d", contadorDeComparacoes);
	printf("\nQuantidade de Trocas: %d", contadorDeTrocas);
	printf("\nTempo Gasto: %g ms.\n", tempoTotal);
}

int main(){
	srand((unsigned) time(NULL));
	int vetor[1000], aux, inicio=0, tamanho=1000;
	int qndRepeticoes=40;
	vetorDesordenado(vetor, inicio, tamanho, qndRepeticoes);
	vetorOrdenado(vetor, inicio, tamanho);
	vetorInversamenteOrdenado(vetor, inicio, tamanho);
}