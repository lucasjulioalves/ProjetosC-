// Declara��es do programa
#include <iostream>
#include <Windows.h>
using namespace std;
// defini��es
#define PAUSA								system("pause")
#define LIMPAR_TELA							system("cls")
#define PAIS_BRASIL							setlocale(LC_ALL, "portuguese_brazil")
#define QTDE_CLIENTES						2000
#define CAMINHO_CADASTRO					"..\\Cadastro.cad"
#define ATIVO								'A'
#define INATIVO								'I'
#define TAM_NOME							40
// op��es do menu do operador
#define INCLUIR_CLIENTE						'I'
#define EXCLUIR_CLIENTE						'E'
#define SACAR_CHEQUE						'C'
#define FAZER_DEPOSITO						'D'
#define MOSTRAR_CLIENTE						'M'
#define SAIR_DO_PROGRAMA					'S'
//
// struct de um cliente
//
typedef struct tagCLIENTE
{
	int nCodigo;							// 1, 2, 3,..........QTDE_CLIENTES
	char cAtivo,							// 'A' - ativo e 'I' - inativo
		cNomeCliente[TAM_NOME + 1];			// nome do cliente
	double dSaldo,							// saldo do cliente
		dVlrTotalCheques,					// total de cheques
		dVlrTotalDepositos;					// total de dep�sitos
} CLIENTE;									// struct de cliente
// Prot�tipos das fun��es
bool PedirCodigoCliente(int *ptrCodigo, char *ptrTransacao);
bool LerPosicional(int nCodigo, CLIENTE *ptrBuffer, FILE *fdCadastro);



