 #include<stdio.h> 
#include<stdlib.h>
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

int troca(int *vetor, int indiceElementoUm,int indiceElementoDois){
	int aux = vetor[indiceElementoUm];
	vetor[indiceElementoUm] = vetor[indiceElementoDois];
	vetor[indiceElementoDois] = aux;
	return *vetor;
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

int inverteVetor(int *vetor, int inicio, int tamanho){
	if(inicio==tamanho){
		return *vetor;
	}
	else{
		troca(vetor, inicio, tamanho-1);
		return inverteVetor(vetor, inicio+1, tamanho-1);
	}
}

int percorreVetor(int *vetor, int i, int j, int maior, int pivo){
	if(j>maior-1){
		troca(vetor, i+1, maior);
		contadorDeTrocas++;
		return (i+1);
	}
	else{
		contadorDeComparacoes++;
		if(vetor[j] < pivo){
			i++;
			troca(vetor, i, j);
			contadorDeTrocas++;
		}
		percorreVetor(vetor, i, j+1, maior, pivo);
	}
}

int particao(int *vetor, int indiceMenor, int indiceMaior){
	int pivo = vetor[indiceMaior];
	int i= (indiceMenor-1);

	return percorreVetor(vetor, i, indiceMenor, indiceMaior, pivo);
}

void quickSort(int *vetor, int indiceMenor, int indiceMaior) {
    if (indiceMenor < indiceMaior){
        int part = particao(vetor, indiceMenor, indiceMaior);

        quickSort(vetor, indiceMenor, part - 1); 
        quickSort(vetor, part + 1, indiceMaior); 
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
		quickSort(vetor,inicio, tamanho-1);
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
	quickSort(vetor, inicio, tamanho-1); //ordena o vetor
	
	tempoTotal=0;
	contadorDeComparacoes=0;
	contadorDeTrocas=0;
	Tempo=0;
	tempo[0] = clock();
	quickSort(vetor, inicio, tamanho-1); //aplicado no vetor ja ordenado
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
	quickSort(vetor, inicio, tamanho-1);
	inverteVetor(vetor, inicio, tamanho);
	//imprimeVetor(vetor, inicio, tamanho);
	printf("\n");
	Tempo=0;
	contadorDeComparacoes=0;
	contadorDeTrocas=0;
	tempo[0] = clock();
	quickSort(vetor, inicio, tamanho-1);
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
	int vetor[1000], tamanho=1000;
	int inicio=0, quantidade=40;
	vetorDesordenado(vetor, inicio, tamanho, quantidade);
	vetorOrdenado(vetor, inicio, tamanho);
	vetorInversamenteOrdenado(vetor, inicio, tamanho);
}