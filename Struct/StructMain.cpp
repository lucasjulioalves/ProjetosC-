//Programa de teste de struct
//FATEC-MC JCB - 03/05/2017 - Versão 0.0
#include "Meu.h"
//Função que matricula aluno
//Parâmetros de entrada
	//nCodigo = codigo do aluno
	//*ptrAcao = ação qu está sendo executada
	//vtAluno = Vetor de alunos
//Retorno true(aluno novo matriculado)
//Retorno false(aluno já cadastrado)
bool MatricularGraduacao(int nCodigo,ALUNO vtAluno[], char *ptrAcao)
{
	SYSTEMTIME stTime;
	cout << "\n\t" << ptrAcao << endl;
	GetLocalTime(&stTime);
	//testar se o aluno ja está matriculado
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
//Função que matricula aluno na Pos
//Parâmetros
	//nCodigo = Codigo do aluno
	//*ptrVtAluno = ponteiro do primeiro byte do vetor de aluno
	// *ptrAcao = Ação executada
//Retornos
	//true = Aluno novo cadastrado
	//false = aluno já cadastrado
bool MatricularPos(int nCodigo, ALUNO *ptrVtAluno, char *ptrAcao)
{
	SYSTEMTIME stTime;
	cout << "\n\t" << ptrAcao << endl;
	GetLocalTime(&stTime);
	//testar se o aluno ja está matriculado
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
	int i, j, 						//indexadores e contadores genéricos
		nQtdePos=0,					//Qtde de alunos de pos graduação
		nCodigo;					// recebe o codigo
	ALUNO stAluno,					//struct para conter os dados de um aluno
		 *ptrAluno,					//ponteiro para vetor de alunos de pós graduação
		 *ptrSalva,					//salva e guarda o vetor de pos
		 vetAlunos[QTDE_ALUNOS];	//vetor de alunos de graduação
	BRASIL;							//acentuação brasileira
	cout << "Qtde alunos de pós: ";
	cin >> nQtdePos;
	//fazer a alocação dinamica de memória para conter nQtdeAlunos
	ptrSalva = ptrAluno = (ALUNO *)malloc(nQtdePos * sizeof(ALUNO)); //precisa usar alocação dinamica de memória para utilizar o vetor *ptrAlunos
	//tem memória para este vetor
	if(ptrAluno == NULL)		//não tem memória?
	{
		cout << "Não tem memória suficiente" << endl;
		PAUSA;
		return;						//volta ao SO
	}

	//temos memoria
	//inicializar o vetor de alunos de´pós
	for(i = 0; i < nQtdePos; i++, ptrAluno++)
	{
		ptrAluno->cAtivo = 'I';
		ptrAluno->nCodigo = i + 1;
		
	}//for i
	ptrAluno = ptrSalva;				//restaura o endereço do vetor de pos
	//inicialziar utilizando artimetica de ponteiros
	for(i = 0; i < nQtdePos; i ++)
	{
		(ptrAluno + i)->cAtivo = 'I';
		(ptrAluno + i)->nCodigo = i + 1;
	}
	//o ptrAluno não se alterou
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
			cout << "Código do alunos de graduação (1 a " << QTDE_ALUNOS << " ) " << endl 
				<< "Ou zero para encerrar a execução: ";
			cin >> nCodigo;
			if(nCodigo == 0){
				free(ptrSalva);
				return;
			}
		}while(nCodigo < 1 || nCodigo > QTDE_ALUNOS);
		if(!MatricularGraduacao(nCodigo, &vetAlunos[0], "Matricular Graduacao" ))
		{
		cout << "Aluno " << nCodigo << " Nome " << vetAlunos[nCodigo - 1].cNome << endl 
			<< "Ja está matriculado " << endl;
		PAUSA;
		}
		else
			cout << "Matriculado com sucesso" << endl;
		do
		{
			cout << "Código do aluno de pós graduação ( 1 a " << nQtdePos << " ): ";
			cin >> nCodigo;
		}while(nCodigo < 1|| nCodigo > nQtdePos);
		//chamar a função que matricula na pós
		if(!MatricularPos(nCodigo, ptrAluno, "Matricular na pós"))
		{
			cout << "Aluno" << nCodigo << " Nome " << (ptrAluno + (nCodigo - 1))->cNome << endl
				<< "Já está matriculado " << endl;
			PAUSA;
		}
		else {
			cout << "Matriculado com sucesso! " << endl;
			PAUSA;
		}
		LIMPAR_TELA;

	}
}//main 
