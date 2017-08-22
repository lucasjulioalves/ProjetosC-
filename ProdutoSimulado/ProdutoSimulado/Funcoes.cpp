#include "Produto.h"
bool PedirCodigoProduto(int *ptrCodigo, char *ptrAcao, int QtdeMax)
{
	cout << "\n\t" << ptrAcao << endl;
	do
	{
		cout << "Código produto 1 a " << QtdeMax << ": ";
		cin >> *ptrCodigo;						// recebe o código
		if (*ptrCodigo == 0)						// cancelou?
			return false;						// indica que cancelou
	} while (*ptrCodigo < 1 || *ptrCodigo > QtdeMax);
	return true;
}

bool LerPosicional(PRODUTO *ptrBuffer, int nCodigo, FILE *fdArquivo)
{
	if (fseek(fdArquivo, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0)
		return false;
	if (fread_s(ptrBuffer, sizeof(PRODUTO), sizeof(PRODUTO), 1, fdArquivo) == 0)
		return false;
	return true;

}

bool GravarPosicional(PRODUTO *ptrBuffer, int nCodigo, FILE *fdArquivo)
{
	if (fseek(fdArquivo, (nCodigo - 1) * sizeof(PRODUTO), SEEK_SET) != 0)
		return false;
	if (fwrite(ptrBuffer, sizeof(PRODUTO), 1, fdArquivo) == 0)
		return false;
	return true;

}