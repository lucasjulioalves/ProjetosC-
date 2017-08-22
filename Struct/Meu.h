//Declarações do programa de struct
#include <iostream>
#include <Windows.h>
using namespace std;
// Definições
#define PAUSA			system("pause")
#define LIMPAR_TELA		system("cls")
#define BRASIL			setlocale(LC_ALL, "portuguese_brazil")
#define QTDE_ALUNOS		1000
//
// struct data
//
typedef struct tagDATA
{
	int nDia, nMes, nAno;     //dia, mês e ano

}DATA;
//
//struct do aluno
//
typedef struct tagALUNO
{
	 int nCodigo;			//codigo do aluno
	 char cNome[41],		//nome do aluno
		 cAtivo;			//aluno ativo = 'A' e 'I' --Aluno ativo ou excluido
	 DATA stDtMatricula;	//data da matricula
	 double dMensaldiade; 	//Mensalidade	
}ALUNO, ALUNA;                     
