// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programa��o - 05/04/2017
// FATEC - Mogi das Cruzes
#include "Hotel.h"
//
// Fun��o principal
//
void main(void)
{
	int  i,									// indice gen�rico
		iIndQuarto,							// para calcular o �ndice do quarto em fun��o do
											//  andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nAndarHotel,						// para receber o n�mero do andar
		nQuartoHotel,						// para receber o n�mero do quarto dentro do andar
		nQtdeTotalQuartos,					// para receber a quantidade total de todo o hotel
		nDiaria;							// para receber a quantidade de diarias	
	char cOpcaoOper,						// local para receber a op��o escolhida do menu
		cNomeHospede[41],					// local para receber o nome do h�spede do hotel
		cWork[200],							// para formata��o de sprintf
		cNomeAluno[] = "Lucas Julio Alves da Costa";
	double dValor;							// local para receber o valor dos servi�os do hotel
	//
	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  est� livre ou ocupado
	//		true - indica que o quarto est� ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor bi-dimensional abaixo indica o nome do hospede que est� ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME + 1];
	// o vetor abaixo indica o valor da di�ria do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo indica o valor total de di�rias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo armazena a quantidade de dias que o cliente est� hospedado
	int vetQuantidadeDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diret�rio principal do projeto que
	// est� LP_ProvaN1_05_04_2017_Tarde para LP_ProvaN1_SeuNomeComLetrasMai�sculasMin�sculas

	// <<<< 01 >>>>
	// Preencher seu nome em cNomeAluno
	// Pedir a quantidade de andares e quartos por andares do hotel ou zeros para cancelar a
	//	execu��o do programa
	do
	{
		cout << "Digite a quantidade de andares do hotel, que deve ser entre " << QTDE_MINIMA_ANDARES << 
			" e " << QUANTIDADE_MAXIMA_ANDARES << endl; 
		cout << "Ou digite 0 para sair: ";
		cin >>nQtdeAndares;
		if(nQtdeAndares == 0) //deseja sair?
			return;
		cout << "Digite a quantidade de quartos de cada andar, que deve ser entre " << QTDE_MINIMA_QUARTOS_ANDAR << 
			" e " << QUANTIDADE_MAXIMA_QUARTOS << endl;
		cout << "Ou digite 0 para sair ";  
		cin >> nQtdeQuartosPorAndar;
		if(nQtdeAndares == 0) //deseja sair?
			return;
	}while(nQtdeAndares < QTDE_MINIMA_ANDARES || nQtdeAndares > QUANTIDADE_MAXIMA_ANDARES &&
			nQtdeQuartosPorAndar < QTDE_MINIMA_ANDARES || nQtdeQuartosPorAndar > QUANTIDADE_MAXIMA_QUARTOS);
	// A quantidade de andares n�o pode ser menor que QTDE_MINIMA_ANDARES e n�o pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES. Se for informado zeros cancelar a execu��o do programa
	// A quantidade de quartos por andar n�o pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS. Se for informado zeros cancelar a execu��o do
	//	programa.
	//

	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da di�ria de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	//		Zerar o total de di�rias de cada quarto.
	nQtdeTotalQuartos = nQtdeAndares * nQtdeQuartosPorAndar;
	for(i = 0; i < nQtdeTotalQuartos; i ++)
	{
		vetLivreOcupado[i] = false;
	}//for i
	while(true)								// loop infinito
	{
		LIMPAR_TELA;
		GetLocalTime(&stTime);
		sprintf_s(cWork, sizeof(cWork), 
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d �s %02d:%02d:%02d\n\t\tOperador: %s Turma: tarde",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de op��es para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// op��o escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a op��o escolhida
		switch(cOpcaoOper)					// avaliar a op��o que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a fun��o PedirAndarQuarto passando os endere�o de nAndarHotel para receber
				//		o n�mero do andar e o endere�o de nQuartoHotel para receber o n�mero do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transa��o � "Check-in de h�spede"
				//		Se retornar false cancelar a transa��o e voltar ao menu
				// somente para testes
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-in de um h�spede"))
					break;									// sai do switch e volta ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar v�lido
				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				//		calcular o iIndQuarto em fun��o do andar e quarto no andar informados.
				// 3 - Verificar se o quarto j� est� ocupado e se estiver exibir ao operador que o
				//		quarto est� ocupado e o nome do h�spede que est� ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				if(vetLivreOcupado[iIndQuarto])   //est� ocupado?
				{
					cout << "O quarto est� ocupado!!!" << endl;
					cout << "O quarto est� ocupado pelo hospede: " << vetNomeHospede[iIndQuarto] << endl;
					PAUSA;
					break;
				}

				// 4 - Pedir o nome do h�spede considerando que tem nome e sobrenome
				
				cout << "Digite o nome completo do hospede: ";
				cin.ignore(1, EOF);
				cin.getline(cNomeHospede, EXTEN_NOME, '\n' );
				strcpy_s(vetNomeHospede[iIndQuarto], sizeof(*vetNomeHospede), cNomeHospede);  //armazena nome do hospede no vetor
				LIMPAR_TELA;
				// 5 - Zerar o total de di�rias do quarto que est� sendo ocupado
				vetQuantidadeDiarias[iIndQuarto] = 0;
				if(nAndarHotel <= 2){   //Menor que dois ?
					vetQuantidadeDiarias[iIndQuarto] += 1;
					vetVlrDiaria[iIndQuarto] = DIARIA_QUARTO_SIMPLES;
					vetLivreOcupado[iIndQuarto] = true;
				}//else if
				else if(nAndarHotel >= 3 && nAndarHotel <= 4){   //Entre 3 e 4?
					vetQuantidadeDiarias[iIndQuarto] += 1;
					vetVlrDiaria[iIndQuarto] = DIARIA_QUARTO_MEDIO;
					vetLivreOcupado[iIndQuarto] = true;
				}//else if

				else if(nAndarHotel >= 5 && nAndarHotel <= 8){  //Entre 5 e 8?
					vetQuantidadeDiarias[iIndQuarto] += 1;
					vetVlrDiaria[iIndQuarto] = DIARIA_QUARTO_SUPER;
					vetLivreOcupado[iIndQuarto] = true;
				}//else if
				else if(nAndarHotel >= 9){					//Maior que 9?
					vetQuantidadeDiarias[iIndQuarto] += 1;
					vetVlrDiaria[iIndQuarto] = DIARIA_QUARTO_SUITE;
					vetLivreOcupado[iIndQuarto] = true;
				}//else if
				//MOSTRANDO OS DADOS
				vetTotalDiarias[iIndQuarto] = vetVlrDiaria[iIndQuarto] * vetQuantidadeDiarias[iIndQuarto]; 	
				LIMPAR_TELA;
				cout << "Cliente cadastrado!" << endl;
				cout << "Nome do cliente...." << vetNomeHospede[iIndQuarto] << endl;
				cout << "Di�ria............." << vetVlrDiaria[iIndQuarto] << endl;
				cout << "Andar.............." << nAndarHotel << endl;
				cout << "Quarto............." << nQuartoHotel << endl;
				PAUSA;
				// 6 - Indicar que este quarto est� ocupado e voltar ao menu
				

				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transa��o 
				//		� "Check-out"
				// 2 - Verificar se a transa��o foi cancelada e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de um h�spede"))   
					break;						//cai fora do switch
				// 3 - Verificar se o quarto est� ocupado e se estiver exibir o nome do h�spede e
				//		o total de di�rias do quarto
				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				if(vetLivreOcupado[iIndQuarto]){
					cout << "O hospede cadastrado: " << vetNomeHospede[iIndQuarto] << endl;
					cout << "O total de di�rias � de: "<<vetTotalDiarias[iIndQuarto] <<"R$" << endl;
					cout << "Dias no Hotel: " << vetQuantidadeDiarias[iIndQuarto]<< endl;
					cout << "Deseja fazer check-out do cliente " << vetNomeHospede[iIndQuarto] << 
						" (S ou N): " << endl;
					cin >> cOpcaoOper;
					toupper(cOpcaoOper);
					if(cOpcaoOper == 'S')  //deseja realizar checkout?
					{
						LIMPAR_TELA;
						vetLivreOcupado[iIndQuarto] = false;
						vetNomeHospede[iIndQuarto][0] = NULL;
						vetVlrDiaria[iIndQuarto] = NULL;
						vetTotalDiarias[iIndQuarto] = 0;
						cout << "Checkout realizado com sucesso! " << endl;
						PAUSA;

					}
					else   //cai fora do switch
						break;
					
				}

				// 4 - Pedir a confirma��o do operador com um S ou N
				//		Se for indicado 'S' ou 's' desocupar o quarto e qualquer outro caractere 
				//		 voltar ao menu. Para desocupar o quarto basta indicar false no vetLivreOcupado
				// 5 - Se o quarto n�o estiver ocupado avisar ao operador e voltar ao menu
				else{
					cout << "N�o h� clientes cadastrados neste quarto" << endl;
					PAUSA;
				}
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				GetLocalTime(&stTime);
				sprintf_s(cWork, sizeof(cWork),
					"\nDeseja lan�ar di�ria em %02d/%02d/%04d?\nConfirma? (S ou N): ",
					stTime.wDay, stTime.wMonth, stTime.wYear);
				cout << cWork;
				cin>> cOpcaoOper;
				toupper(cOpcaoOper);
				if(cOpcaoOper == 'N')        //cancelar opera��o?
				{
					cout << "Opera��o cancelada!" << endl;
					PAUSA;
					break;
				}//if 
				else if(cOpcaoOper == 'S')  //Deseja listar?
				{
					cout << "Lan�ando diarias nos quartos ocupados... Aguarde...." << endl;
					for(i = 0; i < nQtdeTotalQuartos; i++)
					{
						if(vetLivreOcupado[i])    //quarto ocupado?
						{
							vetQuantidadeDiarias[i] += 1;
							vetTotalDiarias[i] = vetVlrDiaria[i] * vetQuantidadeDiarias[i]; 	
						}//if
					}//for i
				}// else if
				cout <<"Todas as di�rias foram lan�adas" << endl;
				PAUSA;
				
				// 2 - Confirmar com o operador se ele realmente deseja lan�ar as di�rias no hor�rio
				//		apresentado
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma di�ria a mais no total de di�rias dos quartos ocupados.
				
				// 4 - Caso o operador n�o confirme voltar ao menu.
				//		Lan�ar di�ria significa pegar o valor da di�ria que foi associada ao quarto e
				//			somar no total das di�rias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora

				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de um h�spede"))
					break;

				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				// 2 - Verificar se o quarto est� ocupado e se n�o estiver, avisar ao operador e voltar ao menu
				if(vetLivreOcupado[iIndQuarto])     //est� ocupado?
				{
					sprintf_s(cWork, sizeof(cWork), "Andar\t Quarto\t H�spede\t                Vlr.Di�ria \t Tot.Di�rias");
					cout << cWork << endl;
					sprintf_s(cWork, sizeof(cWork), "%d\t %d\t %-31s %8.2f\t %8.2f ", 
						nAndarHotel, nQuartoHotel, vetNomeHospede[iIndQuarto], vetVlrDiaria[iIndQuarto], vetTotalDiarias[iIndQuarto] );
					cout << cWork << endl;
					PAUSA;
				}//if
				else
				{
					cout << "N�o h� hospedes no quarto" << endl;
					PAUSA;
					
				}
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do h�spede e valor da
				//		di�ria do quarto e o total de di�rias utilizando o sprintf_s
				//		Formato: Andar Quarto H�spede            Vlr.Di�ria Tot.Di�rias
				//				  A      Q    XXXXXXXXXXXXXXXXX  DDDDD.DD   TTTTTT.TT
				//
				break;						// para sair do switch e voltar ao menu
			case SAIR_DO_PROGRAMA:
				cout << "\nDeseja sair realmente? (S ou N): ";
				cin >> cOpcaoOper;
				if(cOpcaoOper == 'S' || cOpcaoOper == 's')		// sair realmente?
					return;
				break;						// para sair do switch e decidir se vai sair realmente
			default:
				// Avisar que foi escolhida uma op��o errada
				cout << "\nOpcao inv�lida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
