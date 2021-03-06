// Fun��es do programa de Hotel
#include "Hotel.h"
//---[PedirAndarQuarto]--------------------------------------------------------------------
// Fun��o para pedir o andar e o n�mero do quarto no andar
//		
//	Par�metros:
//		Entrada: 
//			int *ptrAndar - endere�o para receber o n�mero do andar de 1 a nQtAndares ou
//							zero para cancelar a transa��o
//			int *ptrQuarto - ponteiro para receber o n�mero do quarto por andar de 1 a
//							  nQtQuartos ou zero para cancelar a transa��o
//			int nQtAndares - quantidade de andares que foi configurada no in�cio do programa
//			int nQtQuartos - idem quantidade de quartos por andar
//			char *ptrTransacao - ponteiro da transa��o que est� sendo realizada
//		Retorno: bool = true - indica que o andar e quarto foram informados
//				 bool = false - indica que a transa��o foi cancelada porque foi informado
//								andar zero ou quarto zero
bool	PedirAndarQuarto(int *ptrAndar, int *ptrQuarto, int nQtAndares, int nQtQuartos, char *ptrTransacao)
{
	// <<<< 08 >>>>
	// 1 - Ficar em loop pedindo o n�mero do andar ou zero para cancelar a transa��o.
	//		O n�mero do andar tem que ser de 1 a nQtAndares
	// 2 - Ficar em loop pedindo o n�mero do quarto ou zeros para cancelar a transa��o
	//		O n�mero do quarto tem que ser de 1 a nQtQuartos

	cout << "\n\t" << ptrTransacao << endl;
	do
	{
		cout << "Andar entre 1 e " << nQtAndares << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> *ptrAndar;						// recebe o andar
		if(*ptrAndar == 0)						// cancelar?
			return false;						// avisa que cancelou
	} while(*ptrAndar < 1 || *ptrAndar > nQtAndares);
	do
	{
		cout << "Quarto do andar entre 1 e " << nQtQuartos << endl
			<< "Ou zero para cancelar a transa��o: ";
		cin >> *ptrQuarto;						// recebe o quarto
		if(*ptrQuarto == 0)						// cancelar?
			return false;						// avisa que cancelar
	}while(*ptrQuarto < 1 || *ptrQuarto > nQtQuartos);

	return true;								// indica que foram informados o andar e o quarto
} 
