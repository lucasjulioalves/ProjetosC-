// Programa de atualiza��o de um arquivo de clientes
// FATEC-MC - LJAC - 10/05/2017 - Vers�o 0.0
#include "Cliente.h"
//
// entry point do programa
//
void main(void)
{
	int i;											// indexador e contador
	char cOpcao,									// op��o do operador
		cWork[200];									// para uso do sprintf_s
	CLIENTE stCliente;								// para conter os dados de um cliente
	FILE *fdCadastro;								// file descriptor do cadastro de clientes
	SYSTEMTIME stTime;								// para receber data e hora

	PAIS_BRASIL;									// acentua��o brasileira
	// vamos abrir o arquivo em modo leitura/grava��o - precisa existir
	if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0)	// erro de abertura?
	{	// � a primeira vez que o programa vai ser executado
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro de abertura?
		{	// foi tentado abrir em modo grava��o/leitura - se existir zera o arquivo
			cout << "Erro de abertura do arquivo: " << CAMINHO_CADASTRO << endl;
			PAUSA;
			return;									// volta ao S.O.
		}
		for(i = 0; i < QTDE_CLIENTES; i++)			// loop de "formata��o" do cadastro
		{
			stCliente.cAtivo = INATIVO;				// cliente inativo
			stCliente.nCodigo = i + 1;				// 1, 2, 3, .......QTDE_CLIENTES
			if(fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0) // erro de grava��o?
			{	// erro de grava��o
				fclose(fdCadastro);					// fechar o arquivo
				cout << "Erro de grava��o!" << endl;
				PAUSA;
				return;								// volta ao S.O.
			}
		} // for i
	} // n�o existe
	//
	// loop infinito do programa
	//
	while(true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);						// data e hora do systema
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-MC - Sistema de Cadastramento de Clientes %02d/%02d/%04d %02d:%02d:%02d",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond);
		cout << cWork << endl;
		cout << INCLUIR_CLIENTE << " - Incluir novo cliente" << endl;
		cout << EXCLUIR_CLIENTE << " - Excluir cliente existente" << endl;
		cout << SACAR_CHEQUE << " - Cheque saque" << endl;
		cout << FAZER_DEPOSITO << " - Depositar em dinheiro" << endl;
		cout << MOSTRAR_CLIENTE << " - Mostrar dados do cliente" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;						// op��o do operador
		cOpcao = toupper(cOpcao);			// converte para mai�scula
		switch(cOpcao)						// avalia a op��o escolhida
		{
			case INCLUIR_CLIENTE:
				break;						// volta ao menu
			case EXCLUIR_CLIENTE:
				break;						// volta ao menu
			case SACAR_CHEQUE:
				break;						// volta ao menu
			case FAZER_DEPOSITO:
				break;						// volta ao menu
			case MOSTRAR_CLIENTE:
				break;						// volta ao menu
			case SAIR_DO_PROGRAMA:
				cout << "Sair realmente? (S ou N): ";
				cin >> cOpcao;
				if(cOpcao == 's' || cOpcao == 'S')		// fechar realmente?
				{
					fclose(fdCadastro);					// fechar o cadastro
					return;								// volta ao S.O.
				}
				break;						// volta ao menu
			default:
				cout << "Op��o inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main