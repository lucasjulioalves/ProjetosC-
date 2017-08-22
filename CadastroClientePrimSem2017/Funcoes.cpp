// Funções do programa de cadastramento de clientes
#include "Cliente.h"
// Função que pede um código de cliente válido
// Se for digitado 0 (zero) indica que o operador quer cancelar a ação ou transação
//	que está sendo executada
//	Parâmetros:
//		Entrada: int *ptrCodigo - ponteiro de uma inteira do chamador da função
//									que receberá um código válido
//				 char *ptrTransacao - string que indica a transação sendo executada
//		Retorno: bool - true - tem um código válido de cliente
//						false - indica que o operador cancelou a transação
bool PedirCodigoCliente(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;
	do
	{
		cout << "Código Cliente (1 a " << QTDE_CLIENTES << "): ";
		cin >> *ptrCodigo;						// recebe o código
		if(*ptrCodigo == 0)						// cancelou?
			return false;						// indica que cancelou
	} while(*ptrCodigo < 1 || *ptrCodigo > QTDE_CLIENTES);
	return true;								// indica que tem um código válido
}

// Função que lê posicional um cliente
//	Parâmetros:
//		Entrada: int nCodigo - código do cliente a ser acessado diretamente 
//				 CLIENTE *ptrBuffer - endereço do buffer de leitura
//				 FILE *fdCadastro - file descriptor do cadastro
//		Retorno: bool - true - tudo OK
//						false - houve erro de fseek ou fread_s
bool LerPosicional(int nCodigo, CLIENTE *ptrBuffer, FILE *fdCadastro)
{
	if(fseek(fdCadastro, nCodigo - 1 * sizeof(CLIENTE), SEEK_SET) != 0) // erro?
		return false;
	if(fread_s(ptrBuffer, sizeof(CLIENTE), sizeof(CLIENTE), 1, fdCadastro) == 0) // erro?
		return false;
	return true;									// indica tudo OK
}
