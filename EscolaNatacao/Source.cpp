#include "Header.h"

void main(void) {
	int caralho;
	int nPeriodo,								// periodo da aula de natação
		nRaia,									// raia da piscina
		iIndRaia,								// indice da raia calculada
		nQtdeParentes,							// quantidade de parentes para desconto
		nQtdeRaiasPiscina,						// para receber a quantidade de raias que a piscina tem
		nQtdeTotalDeRaias,						// qtde total de raias nos três períodos
		i, j;									// índices genéricos
	double dValorMensalidade = 0;					// para calcular a mensalidade
	char cOpcao,								// opcao do operador
		cNomeAluno[] = "Lucas Julio Alves da Costa",
		cRA_Aluno[] = "1840481522039",
		cSobrenome[TAMANHO_SOBRENOME + 1],		// para receber o sobrenome
		cWork[500],								// para sprintf
		nWork[500];
	SYSTEMTIME stTime;							// para data e hora do sistema
	char vetNomesPeriodos[QTDE_PERIODOS][7] =
	{ "Manhã", "Tarde", "Noite" };
	// vetores dos periodos e raias das piscinas
	// vetor que indica se raia livre ou ocupada - true - indica ocupada, false - indica que a raia está livre
	bool vetRaiaLivreOcupada[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];
	// vetor de sobrenomes dos alunos matriculados
	char vetSobrenomesAlunos[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA][TAMANHO_SOBRENOME + 1];
	double vetMensalidades[QTDE_PERIODOS * QTDE_MAXIMA_RAIAS_PISCINA];
	// para duas casas decimais nos valores
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	setlocale(LC_ALL, "portuguese_brazil");		// para acentuação brasileira
	do
	{
		cout << "Digite o número de raias (" << QTDE_MINIMA_RAIAS_PISCINA << " e " << QTDE_MAXIMA_RAIAS_PISCINA << ", ou digite 0 para sair): ";
		cin >> nQtdeRaiasPiscina;
		if (nQtdeRaiasPiscina == 0)
			return;
		break;
	} while (nQtdeRaiasPiscina < QTDE_MINIMA_RAIAS_PISCINA || nQtdeRaiasPiscina > QTDE_MAXIMA_RAIAS_PISCINA);
	nQtdeTotalDeRaias = nQtdeRaiasPiscina * QTDE_PERIODOS; 
	
	for (i = 0; i < nQtdeTotalDeRaias; i++) 
	{
		vetRaiaLivreOcupada[i] = false;
	}
	while (true)
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork),
			"\tFATEC-Escola de Natação %02d/%02d/%04d às %02d:%02d:%02d\n\tOperador: %s Matrícula: %s",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno, cRA_Aluno);
		cout << cWork << endl;
		// exibir o menu
		cout << MATRICULAR_ALUNO << " - Matricular aluno em um período desejado" << endl
			<< CANCELAR_MATRICULA << " - Cancelar a matrícula de um aluno" << endl
			<< LISTAR_PERIODO << " - Listar os alunos de um dado período" << endl
			<< SAIR_DO_PROGRAMA << " - Sair do programa" << endl
			<< "\tSelecione: ";
		cin >> cOpcao;
		cOpcao = toupper(cOpcao);
		switch (cOpcao)
		{
			//exibir o menu
		case MATRICULAR_ALUNO:
			nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Selecione o periodo");
			if (nPeriodo == 0)
				break;
			nRaia = BuscarRaiaLivreNoPeriodo(vetRaiaLivreOcupada, nPeriodo, nQtdeRaiasPiscina);
			if (nRaia == 0)
			{
				cout << "Não há raias disponíveis" << endl;
				PAUSA;
				break;
			}
			iIndRaia = ((nPeriodo - 1) * nQtdeRaiasPiscina) + (nRaia - 1);
			cin.ignore(1, EOF);
			cout << "Digite o sobrenome do aluno: ";
			cin.getline(cSobrenome, TAMANHO_SOBRENOME, '\n');
			strcpy_s(&vetSobrenomesAlunos[iIndRaia][0], sizeof(*vetSobrenomesAlunos), cSobrenome);
			LIMPAR_TELA;
			vetRaiaLivreOcupada[iIndRaia] = true;
			nQtdeParentes = 0;
			for (i = 0; i < nQtdeTotalDeRaias; i++)
			{
				if (vetRaiaLivreOcupada[i] == true && strcmp(vetSobrenomesAlunos[i - 1], cSobrenome) == 0)
				{
					nQtdeParentes++;
				}
			}
			dValorMensalidade = VALOR_MENSALIDADE;
			if (nQtdeParentes > 0 && nQtdeParentes <= 3)
				dValorMensalidade = VALOR_MENSALIDADE - ((VALOR_MENSALIDADE / VALOR_DESCONTO_POR_PARENTE) * nQtdeParentes  );
			else if (nQtdeParentes >= 4)
				dValorMensalidade = VALOR_MENSALIDADE - (VALOR_MENSALIDADE * 0.40);
			vetMensalidades[iIndRaia] = dValorMensalidade;
			cout << "INFORMAÇÕES DO ALUNO CADASTRADO" << endl;
			sprintf_s(cWork, sizeof(cWork), "%-40s", "Raia\t Sobrenome\t Qtde Parentes\t \tMensalidade");
			cout << cWork << endl;
			sprintf_s(cWork, sizeof(cWork), " %d\t  %-16s\t %d\t         %8.2f\t", nRaia, cSobrenome, nQtdeParentes, dValorMensalidade);
			cout << cWork << endl;
			PAUSA;
			break;
		case CANCELAR_MATRICULA:
			if (!PedirPeriodoRaia(&nPeriodo, &nRaia, QTDE_PERIODOS, nQtdeRaiasPiscina, "Selecione o período e a raia"))
				break;
			iIndRaia = ((nPeriodo - 1) * nQtdeRaiasPiscina) + (nRaia - 1);
			sprintf_s(cWork, sizeof(cWork), "%-40s", "Raia\t Sobrenome\t  \tMensalidade");
			cout << cWork << endl; 
			sprintf_s(cWork, sizeof(cWork), "%d\t %-16s\t%8.2f\t", iIndRaia, vetSobrenomesAlunos[iIndRaia], vetMensalidades[iIndRaia]);
			cout << cWork << endl;
			cout << "Deseja cancelar esta matricula? (S ou N): ";
			cin >> cOpcao;
			toupper(cOpcao);
			if (cOpcao == 'S' || cOpcao == 's')
			{
				vetMensalidades[iIndRaia] = NULL;
				vetRaiaLivreOcupada[iIndRaia] = NULL;
				vetSobrenomesAlunos[iIndRaia][0] = NULL;
				dValorMensalidade = 0;
				cout << "Matricula cancelada!" << endl;;
				PAUSA;
			}
			break;
		case LISTAR_PERIODO:
			nPeriodo = PedirPeriodo(QTDE_PERIODOS, "Listar alunos no periodo");
			sprintf_s(cWork, sizeof(cWork), "Listagem dos alunos do periodo %-8s", vetNomesPeriodos[nPeriodo - 1]);
			cout << cWork << endl;
			sprintf_s(cWork, sizeof(cWork), "Sobrenome\t Raia\t \t Mensalidade");
			cout << cWork << endl;
			dValorMensalidade = 0;
			for (i = ((nPeriodo - 1) * (nQtdeRaiasPiscina)); i <= nQtdeRaiasPiscina * (nPeriodo); i++)
			{
				if (vetRaiaLivreOcupada)
				{
					sprintf_s(cWork, sizeof(cWork), " %-17s %d     \t%8.2f", vetSobrenomesAlunos[i], i + 1, vetMensalidades[i]);
					cout << cWork << endl;
					dValorMensalidade += vetMensalidades[i];
				}
			}
			cout << "O valor total das mensalidades é de: " << dValorMensalidade << endl;
			PAUSA;
			break;
		case SAIR_DO_PROGRAMA:
			cout << "Sair do programa (S ou N): ";
			cin >> cOpcao;
			toupper(cOpcao);
			if (cOpcao == 'S')
				return;
			break;
		default:
		PAUSA;
		}
	}
}

int PedirPeriodo(int nQtdePeriodos, char *ptrAcao)
{
	int nPeriodo;
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o período desejado " << endl <<
			"\t1 - Manhã" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> nPeriodo;
	} while (nPeriodo < 0 || nPeriodo > nQtdePeriodos);
	return nPeriodo;
}

int BuscarRaiaLivreNoPeriodo(bool *ptrVetLivreOcup, int nPeriodo, int nQtRaias)
{
	int i, j;
	for (i = (nPeriodo - 1) * nQtRaias, j = 0; j < nQtRaias; i++, j++)
	{
		if (!*(ptrVetLivreOcup + i))
			return (j + 1);
	}
	return 0;
}

bool PedirPeriodoRaia(int *ptrPeriodo, int *ptrRaia,
	int nQtdePeriodos, int nQtRaiasPiscina, char *ptrAcao)
{
	do
	{
		cout << "\n\t" << ptrAcao << endl;
		cout << "Informe o período desejado " << endl <<
			"\t1 - Manhã" << endl << "\t2 - Tarde" << endl << "\t3 - Noite" << endl
			<< "Ou zero para cancelar está ação: ";
		cin >> *ptrPeriodo;
		if (*(ptrPeriodo) == 0) {

			return false;
		}
	} while (*(ptrPeriodo) < PERIODO_MANHA || *(ptrPeriodo) > nQtdePeriodos);
	do
	{
		cout << "Informe entre 1 e " << nQtRaiasPiscina << ": ";
		cin >> *(ptrRaia);
		if (*(ptrRaia) == 0) {
			return false;
		}
	} while (*(ptrRaia) < 1 || *(ptrRaia) > nQtRaiasPiscina);
	return true;
}