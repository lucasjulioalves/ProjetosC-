// Declara��es do programa Raul Gil
#include <iostream>
#include <Windows.h>
using namespace std;
// Defini��es do programa
#define PAUSA									system("pause")
#define LIMPAR_TELA								system("cls")
#define NOTA_MINIMA								0
#define NOTA_MAXIMA								10
#define QTDE_MAXIMA								20
#define QTDE_MINIMA								3
#define MASCULINO								'M'
#define FEMININO								'F'
#define PAIS_BRASIL								setlocale(LC_ALL, "portuguese_brazil")
// prot�tipos das fun��es do programa
void ListarCalouros(char vNomes[][31], char vSexos[], int vNotas[], int nQtde);
void ListarCalourosRaul(char vNomes[][31], char vSexos[], int vNotas[], int nQtde);
void ClassificarPorNota(char vNomes[][31], char vSexos[], int vNotas[], int nQtde);
void ClassificarAlfabetico(char vNomes[][31], char vSexos[], int vNotas[], int nQtde);
#pragma once
