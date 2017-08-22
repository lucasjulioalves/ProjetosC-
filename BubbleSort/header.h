//Declarações do programa
#include <Windows.h>
#include <iostream>
using namespace std;
//definições do programa
#define BRASIL					setlocale(LC_ALL, "portuguese_brazil")
#define LIMPAR_TELA				system("cls")
#define PAUSA					system("pause")
//definição de funções do programa
void bubbleSort(double vet[], int nQtde);