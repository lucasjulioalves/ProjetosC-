//Programa de teste de struct
//FATEC-MC JCB - 03/05/2017 - Vers�o 0.0
#include "Meu.h"
//Fun��o que matricula aluno
//Par�metros de entrada
	//nCodigo = codigo do aluno
	//*ptrAcao = a��o qu est� sendo executada
	//vtAluno = Vetor de alunos
//Retorno true(aluno novo matriculado)
//Retorno false(aluno j� cadastrado)
bool MatricularGraduacao(int nCodigo,ALUNO vtAluno[], char *ptrAcao)
{
	SYSTEMTIME stTime;
	cout << "\n\t" << ptrAcao << endl;
	GetLocalTime(&stTime);
	//testar se o aluno ja est� matriculado
	if(vtAluno[nCodigo - 1].cAtivo == 'A')
	{
		return false;
	}
	cin.ignore(1, EOF);
	cout << "Nome Completo: ";
	cin.getline(vtAluno[nCodigo - 1].cNome, 40, '\n');
	vtAluno[nCodigo - 1].cAtivo = 'A';
	vtAluno[nCodigo - 1].stDtMatricula.nDia = stTime.wDay;
	vtAluno[nCodigo - 1].stDtMatricula.nMes = stTime.wMonth;
	vtAluno[nCodigo - 1].stDtMatricula.nAno = stTime.wYear; 
	return true;

}
//Fun��o que matricula aluno na Pos
//Par�metros
	//nCodigo = Codigo do aluno
	//*ptrVtAluno = ponteiro do primeiro byte do vetor de aluno
	// *ptrAcao = A��o executada
//Retornos
	//true = Aluno novo cadastrado
	//false = aluno j� cadastrado
bool MatricularPos(int nCodigo, ALUNO *ptrVtAluno, char *ptrAcao)
{
	SYSTEMTIME stTime;
	cout << "\n\t" << ptrAcao << endl;
	GetLocalTime(&stTime);
	//testar se o aluno ja est� matriculado
	if((ptrVtAluno + (nCodigo - 1))->cAtivo == 'A')
		return false;
	cin.ignore(1, EOF);
	cout << "Nome Completo: ";
	cin.getline((ptrVtAluno +(nCodigo -1))->cNome, 40, '\n');
	(ptrVtAluno + (nCodigo-1))->cAtivo = 'A';
	(ptrVtAluno + (nCodigo-1))->stDtMatricula.nDia =  stTime.wDay;
	(ptrVtAluno + (nCodigo-1))->stDtMatricula.nMes = stTime.wMonth;
	(ptrVtAluno + (nCodigo-1))->stDtMatricula.nAno = stTime.wYear;
	return true;

}
//
// main
//
void main(void)
{
	int i, j, 						//indexadores e contadores gen�ricos
		nQtdePos=0,					//Qtde de alunos de pos gradua��o
		nCodigo;					// recebe o codigo
	ALUNO stAluno,					//struct para conter os dados de um aluno
		 *ptrAluno,					//ponteiro para vetor de alunos de p�s gradua��o
		 *ptrSalva,					//salva e guarda o vetor de pos
		 vetAlunos[QTDE_ALUNOS];	//vetor de alunos de gradua��o
	BRASIL;							//acentua��o brasileira
	cout << "Qtde alunos de p�s: ";
	cin >> nQtdePos;
	//fazer a aloca��o dinamica de mem�ria para conter nQtdeAlunos
	ptrSalva = ptrAluno = (ALUNO *)malloc(nQtdePos * sizeof(ALUNO)); //precisa usar aloca��o dinamica de mem�ria para utilizar o vetor *ptrAlunos
	//tem mem�ria para este vetor
	if(ptrAluno == NULL)		//n�o tem mem�ria?
	{
		cout << "N�o tem mem�ria suficiente" << endl;
		PAUSA;
		return;						//volta ao SO
	}

	//temos memoria
	//inicializar o vetor de alunos de�p�s
	for(i = 0; i < nQtdePos; i++, ptrAluno++)
	{
		ptrAluno->cAtivo = 'I';
		ptrAluno->nCodigo = i + 1;
		
	}//for i
	ptrAluno = ptrSalva;				//restaura o endere�o do vetor de pos
	//inicialziar utilizando artimetica de ponteiros
	for(i = 0; i < nQtdePos; i ++)
	{
		(ptrAluno + i)->cAtivo = 'I';
		(ptrAluno + i)->nCodigo = i + 1;
	}
	//o ptrAluno n�o se alterou
	//inicialziar o vetor de alunos de pos
	for(i = 0; i < QTDE_ALUNOS; i++)
	{
		vetAlunos[i].cAtivo = 'I';
		vetAlunos[i].nCodigo = i + 1;
	}
	while(true)
	{
		do
		{
			cout << "C�digo do alunos de gradua��o (1 a " << QTDE_ALUNOS << " ) " << endl 
				<< "Ou zero para encerrar a execu��o: ";
			cin >> nCodigo;
			if(nCodigo == 0){
				free(ptrSalva);
				return;
			}
		}while(nCodigo < 1 || nCodigo > QTDE_ALUNOS);
		if(!MatricularGraduacao(nCodigo, &vetAlunos[0], "Matricular Graduacao" ))
		{
		cout << "Aluno " << nCodigo << " Nome " << vetAlunos[nCodigo - 1].cNome << endl 
			<< "Ja est� matriculado " << endl;
		PAUSA;
		}
		else
			cout << "Matriculado com sucesso" << endl;
		do
		{
			cout << "C�digo do aluno de p�s gradua��o ( 1 a " << nQtdePos << " ): ";
			cin >> nCodigo;
		}while(nCodigo < 1|| nCodigo > nQtdePos);
		//chamar a fun��o que matricula na p�s
		if(!MatricularPos(nCodigo, ptrAluno, "Matricular na p�s"))
		{
			cout << "Aluno" << nCodigo << " Nome " << (ptrAluno + (nCodigo - 1))->cNome << endl
				<< "J� est� matriculado " << endl;
			PAUSA;
		}
		else {
			cout << "Matriculado com sucesso! " << endl;
			PAUSA;
		}
		LIMPAR_TELA;

	}
}//main 
