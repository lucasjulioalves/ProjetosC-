//Programa de teste de dois arquivos
//FATEC-MC --LJAC-- 24/05/2017 -- Versão 0.0
#include "Produto.h"
//
//entry point
//
void main(void)
{
	int i;									//indexador e contador generico
	char cOpcao,							//opcao do operador
		cWork[300];							//Para o uso do sprintf
	QUANTIDADE stQuantidade;				//struct que contera a quantidade configurada
	PRODUTO stProduto;						//struct que contera os dados de um produto
	FILE *fdQtde,							//file descriptor do arquivo com a quantidade
		*fdProduto;						//file descriptor do arquivo de produtos
	BRASIL;									//para acentuação brasileira
											//abrir o arquivo de quantidade para saber se é a primeira vez do programa
	if (fopen_s(&fdQtde, CAMINHO_QTDE, "r+b") != 0)
	{
		if (fopen_s(&fdQtde, CAMINHO_QTDE, "w+b") != 0)
		{
			cout << "Erro de abertura de arquivo: " << CAMINHO_QTDE << endl;
			PAUSA;
			return;
		}//if
		do
		{
			cout << "Quantidade de produtos entre " <<
				QTDE_MINIMA_PRODUTOS << " e " << QTDE_MAXIMA_PRODUTOS << " Ou zero para cancelar a execução: ";
			cin >> stQuantidade.nQuantidade;
			if (stQuantidade.nQuantidade == 0)
				return;
		} while (stQuantidade.nQuantidade < QTDE_MINIMA_PRODUTOS ||
			stQuantidade.nQuantidade > QTDE_MAXIMA_PRODUTOS);
		if (fwrite(&stQuantidade, sizeof(QUANTIDADE), 1, fdQtde) == 0)
		{
			fclose(fdQtde);
			cout << "Erro de gravação de quantidade" << endl;
			PAUSA;
			return;
		}//if
		fclose(fdQtde);
	}
	if (fopen_s(&fdProduto, CAMINHO_PRODUTO, "r+b") != 0)
	{
		if (fopen_s(&fdProduto, CAMINHO_PRODUTO, "w+b") != 0)
		{
			cout << "Erro de abertura do arquivo " << CAMINHO_PRODUTO << endl;
			PAUSA;
			return;
		}//if
		for (i = 0; i < QTDE_MAXIMA_PRODUTOS; i++)
		{
			stProduto.cAtivo = INATIVO;
			stProduto.nCodigo = i + 1;
			if (fwrite(&stProduto, sizeof(PRODUTO), 1, fdProduto) == 0)
			{
				cout << "Erro de gravação do arquivo " << CAMINHO_PRODUTO << endl;
				PAUSA;
				return;
			}//if
		}//for i
	}//if
	else
	{
		if (fread_s(&stQuantidade, sizeof(QUANTIDADE), sizeof(QUANTIDADE), 1, fdQtde) == 0)
		{
			cout << "Erro de leitura" << endl;
			PAUSA;
			return;
		}
	}


	do
	{
		cout << "\tIncluir Produto -- " << INCLUIR_PRODUTO << endl;
		cout << "\tExcluir Produto -- " << EXCLUIR_PRODUTO << endl;
		cout << "\tMostrar Produto -- " << MOSTRAR_PRODUTO << endl;
		cout << "\tSair do programa -- " << SAIR << endl;
		cout << "Selecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);
		switch (cOpcao)
		{

		case INCLUIR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Incluir produto", stQuantidade.nQuantidade))
				break;
			if (!LerPosicional(&stProduto, stProduto.nCodigo, fdProduto))
			{
				cout << "Erro de leitura" << endl;
				PAUSA;
				break;
			}
			if (stProduto.cAtivo == ATIVO)
			{
				cout << "O produto de código " << stProduto.nCodigo << " já existe" << endl;
				PAUSA;
				break;
			}
			stProduto.cAtivo = ATIVO;
			cout << "Descrição do produto: ";
			cin.ignore(1, EOF);
			cin.getline(stProduto.cDescricao, TAMANHO_DESC + 1, '\n');
			cout << "Preço do produto: ";
			cin >> stProduto.dPrecoUnit;
			if (!GravarPosicional(&stProduto, stProduto.nCodigo, fdProduto))
			{
				cout << "Erro de gravação" << endl;
				PAUSA;
				break;
			}
			cout << "Arquivo gravado com sucesso" << endl;
			PAUSA;
			break;
		case EXCLUIR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "Excluir produto", stQuantidade.nQuantidade))
				break;
			if (!LerPosicional(&stProduto, stProduto.nCodigo, fdProduto))
			{
				cout << "Erro de leitura" << endl;
				PAUSA;
				break;
			}
			if (stProduto.cAtivo != ATIVO)
			{
				cout << "O produto de código " << stProduto.nCodigo << " não existe" << endl;
				PAUSA;
				break;
			}
			sprintf_s(cWork, sizeof(cWork), "\tCódigo: %d\n\tDescrição: %-40s \n\tPreço: %8.2fR$",
				stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
			cout << cWork << endl;
			cout << "Deseja excluir este produto? (S ou N): ";
			cin >> cOpcao;
			cOpcao = toupper(cOpcao);
			if (cOpcao == 's' || cOpcao == 'S')
			{
				stProduto.cAtivo = INATIVO;
				GravarPosicional(&stProduto, stProduto.nCodigo, fdProduto);
				cout << "Produto excluido" << endl;
				PAUSA;
				break;
			}
			break;
		case MOSTRAR_PRODUTO:
			if (!PedirCodigoProduto(&stProduto.nCodigo, "MOSTRAR PRODUTO", stQuantidade.nQuantidade))
				break;
			if (!LerPosicional(&stProduto, stProduto.nCodigo, fdProduto))
			{
				cout << "Erro de leitura" << endl;
				PAUSA;
				break;
			}
			if (stProduto.cAtivo != ATIVO)
			{
				cout << "Produto de código " << stProduto.nCodigo << " não existe" << endl;
				PAUSA;
				break;
			}
			sprintf_s(cWork, sizeof(cWork), "\tCódigo: %d\n\tDescrição: %-40s\n\tPreço: %8.2fR$",
				stProduto.nCodigo, stProduto.cDescricao, stProduto.dPrecoUnit);
			cout << cWork << endl;
			PAUSA;
			break;
		case SAIR:
			cout << "Deseja sair do programa? (S ou N): ";
			cin >> cOpcao;
			cOpcao = toupper(cOpcao);
			if (cOpcao == 's' || cOpcao == 'S')
			{
				fclose(fdProduto);
				fclose(fdQtde);
				return;
			}
			break;
		default:
			cout << "Opção inválida!" << endl;
			PAUSA;
			break;
			
		}
		LIMPAR_TELA;
	} while (true);

}//main