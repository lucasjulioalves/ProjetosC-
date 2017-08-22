// Programa de atualização de um arquivo de clientes
// FATEC-MC - LJAC - 10/05/2017 - Versão 0.0
#include "Cliente.h"
//
// entry point do programa
//
void main(void)
{
	int i;											// indexador e contador
	char cOpcao,									// opção do operador
		cWork[200];									// para uso do sprintf_s
	CLIENTE stCliente;								// para conter os dados de um cliente
	FILE *fdCadastro;								// file descriptor do cadastro de clientes
	SYSTEMTIME stTime;								// para receber data e hora

	PAIS_BRASIL;									// acentuação brasileira
	// vamos abrir o arquivo em modo leitura/gravação - precisa existir
	if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "r+b") != 0)	// erro de abertura?
	{	// é a primeira vez que o programa vai ser executado
		if(fopen_s(&fdCadastro, CAMINHO_CADASTRO, "w+b") != 0) // erro de abertura?
		{	// foi tentado abrir em modo gravação/leitura - se existir zera o arquivo
			cout << "Erro de abertura do arquivo: " << CAMINHO_CADASTRO << endl;
			PAUSA;
			return;									// volta ao S.O.
		}
		for(i = 0; i < QTDE_CLIENTES; i++)			// loop de "formatação" do cadastro
		{
			stCliente.cAtivo = INATIVO;				// cliente inativo
			stCliente.nCodigo = i + 1;				// 1, 2, 3, .......QTDE_CLIENTES
			if(fwrite(&stCliente, sizeof(CLIENTE), 1, fdCadastro) == 0) // erro de gravação?
			{	// erro de gravação
				fclose(fdCadastro);					// fechar o arquivo
				cout << "Erro de gravação!" << endl;
				PAUSA;
				return;								// volta ao S.O.
			}
		} // for i
	} // não existe
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
		cin >> cOpcao;						// opção do operador
		cOpcao = toupper(cOpcao);			// converte para maiúscula
		switch(cOpcao)						// avalia a opção escolhida
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
				cout << "Opção inválida!" << endl;
				PAUSA;
		} // switch
	} // while
} // main