//Programa com os exerc�cios em sala
//FATEC MC - JCB - 18/03/2017 - Vers�o 0.0
#include "header.h"
//entry point
void main(void)
{
	BRASIL;
	char cVetNomes[5][50],									//vetor com os nomes dos funcion�rios
		 szWork[200];										//vetor de aux�lio
	double dVetSalarios[5],									//vetor com os salarios dos funcionarios
		   dAuxiliar;										//vari�vel de auxilio do bubble sort
	int i;													//vari�vel gen�rica de contagem
	bool flagHouveTroca = false;							//indica se houve troca ou n�o
	//preenchendo o vetor de nomes e de salarios
	for (i = 0; i < 5; i++)
	{
		cout << "Digite o nome do " << i + 1 << "� " << "funcion�rio: ";
		cin >> cVetNomes[i];
		cout << "Digite o sal�rio do " << i + 1 << "� " << "funcion�rio: ";
		cin >> dVetSalarios[i];
		cout << endl;
	}//for i
	LIMPAR_TELA;
	//ordenando os vetores
	do
	{
		flagHouveTroca = false;								//ainda n�o houve troca

		for (i = 0; i < 5 - 1; i++)
		{
			if (strcmp(cVetNomes[i], cVetNomes[i + 1]) > 0)			//nomes fora de ordem?
			{
				//ordenando os nomes
				strcpy_s(szWork, sizeof(cVetNomes[i]), cVetNomes[i]);
				strcpy_s(cVetNomes[i], sizeof(cVetNomes[i + 1]), cVetNomes[i + 1]);
				strcpy_s(cVetNomes[i + 1], sizeof(cVetNomes[i + 1]), szWork);
				flagHouveTroca = true;								//indica que houve troca;
			}
		}//for i
	} while (flagHouveTroca);
	bubbleSort(dVetSalarios, 5);									//arrumando o vetor de sal�rios
	//listando os vetores
	sprintf_s(szWork, "Nome                                  Sal�rio");
	cout << szWork << endl;;
	for (i = 0; i < 5; i++)
	{
		sprintf_s(szWork, "%-49s%9.2f",
			cVetNomes[i], dVetSalarios[i]);
		cout << szWork << endl;;
	}
}