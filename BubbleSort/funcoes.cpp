//Fun��es do programa
#include "header.h"
// Fun��o que classifica um vetor em ordem crescente utilizando o algoritmo BubbleSort de D.Flores (1958)
//Par�metros:
//			Entrada: double vet[] - endere�o de um vetor double
//					 nQtde - quantidade de elementos do vetor
//			Retorno void
void bubbleSort(double vet[], int nQtde)
{
	bool flagHouveTroca = false;			//indica se houve troca no bubble sort
	int i;									//indexador e contador gen�rico
	double dAuxiliar;							//para permitir a troca de posi��o
	do
	{
		flagHouveTroca = false;				//ainda n�o houve troca
		for (i = 0; i < nQtde - 1; i++)
		{ //loop de compara��o dois a dois
			if (vet[i] > vet[i + 1])		//fora de ordem?
			{
				dAuxiliar = vet[i];			//salva o elemento [i]
				vet[i] = vet[i + 1];		//salva o elemento [i+1] no [i]
				vet[i + 1] = dAuxiliar;		//elemento [i] troca de posi��o
				flagHouveTroca = true;		//indica que houve troca
			}
		}//for i
		

		
	} while (flagHouveTroca);
	
}//bubbleSort