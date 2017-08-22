// Hotel.cpp - Programa de Hotel para prova de Linguagem de Programação - 05/04/2017
// FATEC - Mogi das Cruzes
#include "Hotel.h"
//
// Função principal
//
void main(void)
{
	int  i,									// indice genérico
		iIndQuarto,							// para calcular o índice do quarto em função do
											//  andar e o quarto dentro do andar
		nQtdeAndares,						// para receber a quantidade de andares do hotel
		nQtdeQuartosPorAndar,				// para receber a quantidade de quartos por andar
		nAndarHotel,						// para receber o número do andar
		nQuartoHotel,						// para receber o número do quarto dentro do andar
		nQtdeTotalQuartos,					// para receber a quantidade total de todo o hotel
		nDiaria;							// para receber a quantidade de diarias	
	char cOpcaoOper,						// local para receber a opção escolhida do menu
		cNomeHospede[41],					// local para receber o nome do hóspede do hotel
		cWork[200],							// para formatação de sprintf
		cNomeAluno[] = "Lucas Julio Alves da Costa";
	double dValor;							// local para receber o valor dos serviços do hotel
	//
	// vetores do sistema de hotel
	//
	// o vetor abaixo indica quando o quarto dentro de um andar  está livre ou ocupado
	//		true - indica que o quarto está ocupado
	bool vetLivreOcupado[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor bi-dimensional abaixo indica o nome do hospede que está ocupando o quarto
	char vetNomeHospede[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS][EXTEN_NOME + 1];
	// o vetor abaixo indica o valor da diária do quarto
	double vetVlrDiaria[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo indica o valor total de diárias do quarto
	double vetTotalDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	// o vetor abaixo armazena a quantidade de dias que o cliente está hospedado
	int vetQuantidadeDiarias[QUANTIDADE_MAXIMA_ANDARES * QUANTIDADE_MAXIMA_QUARTOS];
	SYSTEMTIME stTime;						// para buscar data e hora

	setlocale(LC_ALL, "portuguese_brazil");
	// comandos para estabelecer o numero de casas decimais
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);						// duas casas decimais
	// <<<<<<0>>>>>>> - Antes de entregar o Pen drive - renomear o diretório principal do projeto que
	// está LP_ProvaN1_05_04_2017_Tarde para LP_ProvaN1_SeuNomeComLetrasMaiúsculasMinúsculas

	// <<<< 01 >>>>
	// Preencher seu nome em cNomeAluno
	// Pedir a quantidade de andares e quartos por andares do hotel ou zeros para cancelar a
	//	execução do programa
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
	// A quantidade de andares não pode ser menor que QTDE_MINIMA_ANDARES e não pode ser maior
	//	que a QUANTIDADE_MAXIMA_ANDARES. Se for informado zeros cancelar a execução do programa
	// A quantidade de quartos por andar não pode ser menor que QTDE_MINIMA_QUARTOS_ANDAR
	//  ou maior que QUANTIDADE_MAXIMA_QUARTOS. Se for informado zeros cancelar a execução do
	//	programa.
	//

	// Inicializar o vetor vetLivreOcupado fazendo com que todos os quartos estejam livres e 
	//		associar a cada quarto o valor correspondente da diária de acordo com o andar do
	//		mesmo de acordo com que foi definido no Hotel.h
	//		Zerar o total de diárias de cada quarto.
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
			"\n\tFATEC-MC - Sistema de Hotel %02d/%02d/%04d às %02d:%02d:%02d\n\t\tOperador: %s Turma: tarde",
			stTime.wDay, stTime.wMonth, stTime.wYear,
			stTime.wHour, stTime.wMinute, stTime.wSecond,
			cNomeAluno);
		cout << cWork << endl;
		// Mostrar o menu de opções para o operador
		cout << FAZER_CHECK_IN << " - Check-in de um hospede" << endl;
		cout << FAZER_CHECK_OUT << " - Check-out de um hospede" << endl;
		cout << LANCAR_DIARIA << " - Lancar diarias em todos os quartos ocupados" << endl;
		cout << LISTAR_UM_QUARTO << " - Listar um quarto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin	 >> cOpcaoOper;					// opção escolhida pelo operador
		cOpcaoOper = toupper(cOpcaoOper);	// converte para upper case a opção escolhida
		switch(cOpcaoOper)					// avaliar a opção que foi escolhida pelo operador
		{
			case FAZER_CHECK_IN:
				// <<<< 02 >>>>
				// 1 - Chamar a função PedirAndarQuarto passando os endereço de nAndarHotel para receber
				//		o número do andar e o endereço de nQuartoHotel para receber o número do quarto no
				//			andar, quantidade de andares e quartos por andar que foram configurados e
				//			indicar que a transação é "Check-in de hóspede"
				//		Se retornar false cancelar a transação e voltar ao menu
				// somente para testes
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-in de um hóspede"))
					break;									// sai do switch e volta ao menu
				// 2 - Se retornou true indicando que foram informados andar e quarto no andar válido
				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				//		calcular o iIndQuarto em função do andar e quarto no andar informados.
				// 3 - Verificar se o quarto já está ocupado e se estiver exibir ao operador que o
				//		quarto está ocupado e o nome do hóspede que está ocupando o quarto, dar uma
				//		pausa para o operador poder ler e voltar ao menu.
				if(vetLivreOcupado[iIndQuarto])   //está ocupado?
				{
					cout << "O quarto está ocupado!!!" << endl;
					cout << "O quarto está ocupado pelo hospede: " << vetNomeHospede[iIndQuarto] << endl;
					PAUSA;
					break;
				}

				// 4 - Pedir o nome do hóspede considerando que tem nome e sobrenome
				
				cout << "Digite o nome completo do hospede: ";
				cin.ignore(1, EOF);
				cin.getline(cNomeHospede, EXTEN_NOME, '\n' );
				strcpy_s(vetNomeHospede[iIndQuarto], sizeof(*vetNomeHospede), cNomeHospede);  //armazena nome do hospede no vetor
				LIMPAR_TELA;
				// 5 - Zerar o total de diárias do quarto que está sendo ocupado
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
				cout << "Diária............." << vetVlrDiaria[iIndQuarto] << endl;
				cout << "Andar.............." << nAndarHotel << endl;
				cout << "Quarto............." << nQuartoHotel << endl;
				PAUSA;
				// 6 - Indicar que este quarto está ocupado e voltar ao menu
				

				break;						// para sair do switch e voltar ao menu
			case FAZER_CHECK_OUT:
				// <<<< 03 >>>>
				// 1 - Pedir o andar e o quarto da mesma forma que no item anterior indicando que a transação 
				//		é "Check-out"
				// 2 - Verificar se a transação foi cancelada e voltar ao menu
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de um hóspede"))   
					break;						//cai fora do switch
				// 3 - Verificar se o quarto está ocupado e se estiver exibir o nome do hóspede e
				//		o total de diárias do quarto
				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				if(vetLivreOcupado[iIndQuarto]){
					cout << "O hospede cadastrado: " << vetNomeHospede[iIndQuarto] << endl;
					cout << "O total de diárias é de: "<<vetTotalDiarias[iIndQuarto] <<"R$" << endl;
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

				// 4 - Pedir a confirmação do operador com um S ou N
				//		Se for indicado 'S' ou 's' desocupar o quarto e qualquer outro caractere 
				//		 voltar ao menu. Para desocupar o quarto basta indicar false no vetLivreOcupado
				// 5 - Se o quarto não estiver ocupado avisar ao operador e voltar ao menu
				else{
					cout << "Não há clientes cadastrados neste quarto" << endl;
					PAUSA;
				}
				break;						// para sair do switch e voltar ao menu
			case LANCAR_DIARIA:
				// <<<< 05 >>>> 
				// 1 - Pedir a data e hora do sistema e apresentar ao operador
				GetLocalTime(&stTime);
				sprintf_s(cWork, sizeof(cWork),
					"\nDeseja lançar diária em %02d/%02d/%04d?\nConfirma? (S ou N): ",
					stTime.wDay, stTime.wMonth, stTime.wYear);
				cout << cWork;
				cin>> cOpcaoOper;
				toupper(cOpcaoOper);
				if(cOpcaoOper == 'N')        //cancelar operação?
				{
					cout << "Operação cancelada!" << endl;
					PAUSA;
					break;
				}//if 
				else if(cOpcaoOper == 'S')  //Deseja listar?
				{
					cout << "Lançando diarias nos quartos ocupados... Aguarde...." << endl;
					for(i = 0; i < nQtdeTotalQuartos; i++)
					{
						if(vetLivreOcupado[i])    //quarto ocupado?
						{
							vetQuantidadeDiarias[i] += 1;
							vetTotalDiarias[i] = vetVlrDiaria[i] * vetQuantidadeDiarias[i]; 	
						}//if
					}//for i
				}// else if
				cout <<"Todas as diárias foram lançadas" << endl;
				PAUSA;
				
				// 2 - Confirmar com o operador se ele realmente deseja lançar as diárias no horário
				//		apresentado
				// 3 - Se o operador confirmar percorrer o vetor de quartos livres e ocupados e 
				//			somar uma diária a mais no total de diárias dos quartos ocupados.
				
				// 4 - Caso o operador não confirme voltar ao menu.
				//		Lançar diária significa pegar o valor da diária que foi associada ao quarto e
				//			somar no total das diárias e do quarto.
				// Para buscar a data e hora do sistema utilizar o seguinte comando:
				//		GetLocalTime(&stTime);
				//		stTime.wDay, stTime.wHour e etc. tem o valores correspondentes a data e hora

				break;						// para sair do switch e voltar ao menu
			case LISTAR_UM_QUARTO:
				// <<<< 06 >>>> 
				// 1 - Pedir Andar e Quarto conforme itens anteriores
				if(!PedirAndarQuarto(&nAndarHotel, &nQuartoHotel, 
					nQtdeAndares, nQtdeQuartosPorAndar, "Check-out de um hóspede"))
					break;

				iIndQuarto = ((nAndarHotel - 1) * nQtdeQuartosPorAndar) + (nQuartoHotel - 1);
				// 2 - Verificar se o quarto está ocupado e se não estiver, avisar ao operador e voltar ao menu
				if(vetLivreOcupado[iIndQuarto])     //está ocupado?
				{
					sprintf_s(cWork, sizeof(cWork), "Andar\t Quarto\t Hóspede\t                Vlr.Diária \t Tot.Diárias");
					cout << cWork << endl;
					sprintf_s(cWork, sizeof(cWork), "%d\t %d\t %-31s %8.2f\t %8.2f ", 
						nAndarHotel, nQuartoHotel, vetNomeHospede[iIndQuarto], vetVlrDiaria[iIndQuarto], vetTotalDiarias[iIndQuarto] );
					cout << cWork << endl;
					PAUSA;
				}//if
				else
				{
					cout << "Não há hospedes no quarto" << endl;
					PAUSA;
					
				}
				// 3 - Se estiver ocupado listar os dados do quarto indicando nome do hóspede e valor da
				//		diária do quarto e o total de diárias utilizando o sprintf_s
				//		Formato: Andar Quarto Hóspede            Vlr.Diária Tot.Diárias
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
				// Avisar que foi escolhida uma opção errada
				cout << "\nOpcao inválida!" << endl;
				PAUSA;
		} // switch
	} // while(true)
} // main
