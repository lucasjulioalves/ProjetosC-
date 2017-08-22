// Programa Raul Gil
// FATEC - MC - JCB - 22/03/2017 - Versão 0.0
#include "RaulGil.h"
//
// Entry point do programa
//
void main(void)
{
	int i,											// indexador e contador genérico
		nNotaTrono = -1,								// melhor nota no trono
		nQtde = 0,									// quantidade de calouros que irá cantar
		nIndiceTrono = 0;							// indice do calouro que está no trono
	int vetNotas[QTDE_MAXIMA];						// vetor de notas dos calouros que vão cantar
	char vetSexos[QTDE_MAXIMA],						// vetor de sexos
		vetNomes[QTDE_MAXIMA][31];					// vetor bi-dimensional para os nomes
	PAIS_BRASIL;									// acentuação brasileira
													// pedir uma quantidade válida
	do
	{
		cout << "Informe a quantidade de calouros entre " <<
			QTDE_MINIMA << " e " << QTDE_MAXIMA << endl
			<< "Ou zero para cancelar a execução do programa: ";
		cin >> nQtde;
		if (nQtde == 0)								// cancelar?
			return;									// volta ao sistema operacional
	} while (nQtde < QTDE_MINIMA || nQtde > QTDE_MAXIMA);
	// loop para receber os calouros que irão cantar
	for (i = 0; i < nQtde; i++)
	{
		cout << "Nome do calouro de ordem " << i + 1 << " de " << nQtde << " : ";
		cin.ignore(1, EOF);							// limpar o buffer do teclado (Tecla Enter)
		cin.getline(vetNomes[i], 30, '\n');			// nome com sobrenome
													// pedir o sexo do calouro que tem que ser válido
		do
		{
			cout << "Informe o sexo do calouro " << vetNomes[i] << " (" << MASCULINO
				<< "-Masculino e " << FEMININO << "-Feminino): ";
			cin >> vetSexos[i];
			vetSexos[i] = toupper(vetSexos[i]);		// converte para maiúscula
		} while (vetSexos[i] != MASCULINO && vetSexos[i] != FEMININO);
		// pedir e receber a nota do calouro
		do
		{
			cout << "Nota entre " << NOTA_MINIMA << " e " << NOTA_MAXIMA << " : ";
			cin >> vetNotas[i];
		} while (vetNotas[i] < NOTA_MINIMA || vetNotas[i] > NOTA_MAXIMA);
		// verificar se o calouro vai para o trono
		if (vetNotas[i] > nNotaTrono)				// vai para o trono?
		{	// vai para o trono
			nNotaTrono = vetNotas[i];				// salva a melhor nota no trono
			nIndiceTrono = i;						// salva o indice do melhor até o momento
		}
	} // for i
	  // todos os calouros já cantaram
	cout << "O melhor calouro foi: " << vetNomes[nIndiceTrono] << " Sexo: " <<
		vetSexos[nIndiceTrono] << " Nota: " << vetNotas[nIndiceTrono] << endl;
	PAUSA;
	// listar os calouros que cantaram hoje
	LIMPAR_TELA;
	ClassificarPorNota(&vetNomes[0], vetSexos, vetNotas, nQtde);
	/*cout << "\n\tListagem dos calouros que cantaram hoje" << endl;
	ListarCalouros(&vetNomes[0], vetSexos, vetNotas, nQtde);
	LIMPAR_TELA;
	cout << "\n\tListagem dos calouros que cantaram hoje" << endl;
	ListarCalourosRaul(&vetNomes[0], vetSexos, vetNotas, nQtde);
	// classificar os calouros em ordem decrescente de nota
	ClassificarPorNota(&vetNomes[0], vetSexos, vetNotas, nQtde);
	// listar os calouros 
	LIMPAR_TELA;
	cout << "\n\tListagem dos calouros em ordem decrescente de nota" << endl;
	ListarCalouros(&vetNomes[0], vetSexos, vetNotas, nQtde);
	// classificar os calouros em ordem alfabética
	ClassificarAlfabetico(&vetNomes[0], vetSexos, vetNotas, nQtde);
	// listar os calouros
	LIMPAR_TELA;
	cout << "\n\tListagem dos calouros em ordem alfabética" << endl;
	ListarCalouros(&vetNomes[0], vetSexos, vetNotas, nQtde);*/
} // main

  // Função que lista os vetores de calouros
  // Parâmetros:
  //	Entrada: char vNomes[][31] - endereço do nome do primeiro calouro do vetor
  //			 char vSexos[] - endereço do sexo do primeiro calouro do vetor
  //			 int vNotas[] - endereço da nota do primeiro calouro do vetor
  //			 int nQtde - quantidade de calouros que cantou hoje

void ListarCalouros(char vNomes[][31], char vSexos[], int vNotas[], int nQtde)
{
	int i;								// indice e contador genérico
	char cWork[200];					// area de trabalho para o sprintf_s
	sprintf_s(cWork, sizeof(cWork), "Nome                           Sexo  Nota");
	cout << cWork << endl;
	// loop de emissão do calouros
	for (i = 0; i < nQtde; i++)
	{
		sprintf_s(cWork, sizeof(cWork), "%-31s %c    %2d",
			vNomes[i], vSexos[i], vNotas[i]);
		cout << cWork << endl;
	} // for i
	cout << "\tFim da Listagem" << endl;
	PAUSA;
}
// Função que lista os vetores de calouros
// Parâmetros:
//	Entrada: char vNomes[][31] - endereço do nome do primeiro calouro do vetor
//			 char vSexos[] - endereço do sexo do primeiro calouro do vetor
//			 int vNotas[] - endereço da nota do primeiro calouro do vetor
//			 int nQtde - quantidade de calouros que cantou hoje

void ListarCalourosRaul(char vNomes[][31], char vSexos[], int vNotas[], int nQtde)
{
	int i;								// indice e contador genérico
										// loop de emissão do calouros
	for (i = 0; i < nQtde; i++)
	{
		cout << "Nome: " << vNomes[i] << " Sexo: " << vSexos[i] << " Nota: " << vNotas[i] << endl;
	} // for i
	cout << "\tFim da Listagem" << endl;
	PAUSA;
}
// Função que classifica os calouros em ordem decrescente de nota
//	Algoritmo BubleSort de D. Flores
// Parâmetros:
//	Entrada: char vNomes[][31] - endereço do nome do primeiro calouro do vetor
//			 char vSexos[] - endereço do sexo do primeiro calouro do vetor
//			 int vNotas[] - endereço da nota do primeiro calouro do vetor
//			 int nQtde - quantidade de calouros que cantou hoje
void ClassificarPorNota(char vNomes[][31], char vSexos[], int vNotas[], int nQtde)
{
	int i, nAuxiliar;
	char szWork[200];
	bool flagHouveTroca = false;

	do
	{
		flagHouveTroca = false;
		for (i = 0; i < nQtde; i++)
		{
			if (vNotas[i] > vNotas[i+1])
			{
				nAuxiliar = vNotas[i];
				vNotas[i] = vNotas[i + 1];
				vNotas[i + 1] = nAuxiliar;

				strcpy_s(szWork, sizeof(vNomes[i]), vNomes[i]);
				strcpy_s(vNomes[i], sizeof(vNomes[i+1]), vNomes[i+1]);
				strcpy_s(vNomes[i + 1], sizeof(vNomes[i + 1]), szWork);
				flagHouveTroca = true;
			}
		}
	} while (flagHouveTroca);

	for (i = 0; i < nQtde; i++)
	{
		cout << "Nome: " << vNomes[i] << " Sexo: " << vSexos[i] << " Nota: " << vNotas[i] << endl;
	} // for i
	cout << "\tFim da Listagem" << endl;
	PAUSA;

}
// Função que classifica os calouros em ordem alfabética
//	Algoritmo BubleSort de D. Flores
// Parâmetros:
//	Entrada: char vNomes[][31] - endereço do nome do primeiro calouro do vetor
//			 char vSexos[] - endereço do sexo do primeiro calouro do vetor
//			 int vNotas[] - endereço da nota do primeiro calouro do vetor
//			 int nQtde - quantidade de calouros que cantou hoje
void ClassificarAlfabetico(char vNomes[][31], char vSexos[], int vNotas[], int nQtde)
{
}



