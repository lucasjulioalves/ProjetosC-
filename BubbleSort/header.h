//Declara��es do programa
#include <Windows.h>
#include <iostream>
using namespace std;
//defini��es do programa
#define BRASIL					setlocale(LC_ALL, "portuguese_brazil")
#define LIMPAR_TELA				system("cls")
#define PAUSA					system("pause")
//defini��o de fun��es do programa
void bubbleSort(double vet[], int nQtde);