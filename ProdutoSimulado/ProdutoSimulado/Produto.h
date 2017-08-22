#include <Windows.h>
#include <iostream>
using namespace std;
//Defines
#define PAUSA					system("pause")
#define LIMPAR_TELA				system("cls")
#define BRASIL					setlocale(LC_ALL, "portuguese_brazil")
#define QTDE_MAXIMA_PRODUTOS	10000
#define QTDE_MINIMA_PRODUTOS	1000
#define CAMINHO_QTDE			"..\\Quantidades.qtd"
#define CAMINHO_PRODUTO			"..\\Produtos.cad"
#define ATIVO					'A'
#define INATIVO					'I'
#define TAMANHO_DESC			40
#define INCLUIR_PRODUTO			'I'
#define EXCLUIR_PRODUTO			'E'
#define MOSTRAR_PRODUTO			'M'
#define SAIR					'S'

//
//struct do produto
//
typedef struct tagPRODUTO
{
	int nCodigo;						//código de 1,2,3... até a qtde dimensionada
	char cAtivo,						//produto ativo = 'A' e inativo = 'I'
		cDescricao[TAMANHO_DESC + 1];	//Descrição do produto
	double dPrecoUnit;					//Preço unitario do produto

}PRODUTO;
//
//struct da quantidade
//
typedef struct tagQUANTIDADE
{
	int nQuantidade;					//quantidade dimesionada de produtos
}QUANTIDADE;

//Protótipos
bool PedirCodigoProduto(int *ptrCodigo, char *ptrAcao, int QtdeMax);
bool LerPosicional(PRODUTO *ptrBuffer, int nCodigo, FILE *fdArquivo);
bool GravarPosicional(PRODUTO *ptrBuffer, int nCodigo, FILE *fdArquivo); 
