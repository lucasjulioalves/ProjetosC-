//Funções do programa
#include "header.h"
// Função que classifica um vetor em ordem crescente utilizando o algoritmo BubbleSort de D.Flores (1958)
//Parâmetros:
//			Entrada: double vet[] - endereço de um vetor double
//					 nQtde - quantidade de elementos do vetor
//			Retorno void
void bubbleSort(double vet[], int nQtde)
{
	bool flagHouveTroca = false;			//indica se houve troca no bubble sort
	int i;									//indexador e contador genérico
	double dAuxiliar;							//para permitir a troca de posição
	do
	{
		flagHouveTroca = false;				//ainda não houve troca
		for (i = 0; i < nQtde - 1; i++)
		{ //loop de comparação dois a dois
			if (vet[i] > vet[i + 1])		//fora de ordem?
			{
				dAuxiliar = vet[i];			//salva o elemento [i]
				vet[i] = vet[i + 1];		//salva o elemento [i+1] no [i]
				vet[i + 1] = dAuxiliar;		//elemento [i] troca de posição
				flagHouveTroca = true;		//indica que houve troca
			}
		}//for i
		

		
	} while (flagHouveTroca);
	
}//bubbleSort