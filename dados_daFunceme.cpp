Romildo José da Silva
#include <iostream>
#include <fstream>
#include <cmath>

#include "dados_daFunceme.hpp"
#define POSTOS "/home/prof/Download/coordenadasDengueFunceme/Postos/postos_comCoordenadasDiferentesForaOceano.txt"

using namespace std;
const double dados_daFunceme::Epsilon = 1e-6;

void mapTipoPrecipitacao( map<tipoPrecipitacao, string> &tipoInformacao )
{
	tipoInformacao[ ANO_SEM_INFO ] = string( "ANO_SEM_INFO" );
	tipoInformacao[ MES_SEM_INFO ] = string( "MES_SEM_INFO" );
	tipoInformacao[ MES_SEM_INFO ] = string( "MES_SEM_INFO" );
	tipoInformacao[ DIA_INVALIDO ] = string( "DIA_INVALIDO" );
	tipoInformacao[ MES_INVALIDO ] = string( "MES_INVALIDO" );
	tipoInformacao[ ID_INVALIDO ] = string( "ID_INVALIDO" );
	tipoInformacao[ INFORMADA ] = string( "INFORMADA" );
	tipoInformacao[ INDEFINIDA ] = string( "INDEFINIDA" );

}

dados_daFunceme::dados_daFunceme()
{
	ifstream inFile( POSTOS , ios::in);	
	char c;
	char pontoVirgula;
	unsigned int Identidade, antIdentidade=0;
	postoFunceme tempPosto;
	indices_deChuva tempIndices;
	double Precipitacao;

	// Desprezando a primeira linha!
	while( (c=inFile.get()) != '\n' );

	while( inFile >> Identidade ){

		// Teste para saber se um novo posto será lido!
		if( Identidade != antIdentidade ){
			//Leitura da primeira linha de um novo posto!

			if ( antIdentidade!=0 ){//Para leitura do primeiro posto!
				postosFunceme.push_back( tempPosto );
				tempPosto.Cidade.clear();
				tempPosto.nomePosto.clear();
				tempPosto.Indices.clear();
			}

			tempPosto.Identidade = Identidade;

			inFile >> pontoVirgula;
			
			// begin: os dados do posto são lidos aqui!
			while( (c=inFile.get()) != ';' ){
				tempPosto.Cidade.push_back(c);
			}

			while( (c=inFile.get()) != ';' ){
				tempPosto.nomePosto.push_back(c);
			}

			inFile >> tempPosto.yCoord;
			inFile >> pontoVirgula;
			inFile >> tempPosto.xCoord;		
			inFile >> pontoVirgula;
			// end:
			
			inFile >> tempIndices.Ano;
			inFile >> pontoVirgula;
			inFile >> tempIndices.Mes;
			inFile >> pontoVirgula;
			inFile >> tempIndices.Total;

			for( unsigned int i=1; i<=31; ++i){
				inFile >> pontoVirgula;
				inFile >> Precipitacao;
				tempIndices.Precipitacoes.push_back( Precipitacao );
			}

			tempPosto.Indices.push_back( tempIndices );
			tempIndices.Precipitacoes.clear();

		} 
		else{
			// Leitura das demais linhas do novo posto!

			// begin: não é necessário ler novamente os dados do posto!
			while( (c=inFile.get()) != ';' );
			while( (c=inFile.get()) != ';' );
			while( (c=inFile.get()) != ';' );
			while( (c=inFile.get()) != ';' );
			while( (c=inFile.get()) != ';' );
			// end:

			inFile >> tempIndices.Ano;
			inFile >> pontoVirgula;
			inFile >> tempIndices.Mes;
			inFile >> pontoVirgula;
			inFile >> tempIndices.Total;
		
			for( unsigned int i=1; i<=31; ++i){
				inFile >> pontoVirgula;
				inFile >> Precipitacao;
				tempIndices.Precipitacoes.push_back( Precipitacao );
			}

			tempPosto.Indices.push_back( tempIndices );
			tempIndices.Precipitacoes.clear();
		}

		antIdentidade=Identidade;
	}

}

void dados_daFunceme::escreverDados()
{
	vector<postoFunceme>::iterator ptIter;

	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter ){
		vector<indices_deChuva>::iterator icIter;

		for( icIter=ptIter->Indices.begin(); icIter!=ptIter->Indices.end(); icIter++ ){

			cout << ptIter->Identidade << ";";
			cout << ptIter->Cidade << ";";
			cout << ptIter->nomePosto << ";";
			cout << ptIter->xCoord << ";";
			cout << ptIter->yCoord << ";";
			cout << icIter->Ano << ";";
			cout << icIter->Mes << ";";
			cout << icIter->Total;

			vector<double>::iterator dIter;
			
			for( dIter=icIter->Precipitacoes.begin(); dIter!=icIter->Precipitacoes.end();
				 ++dIter )
				cout  << ";" << *dIter;
			cout << "\n";
		}
	}
}

tipoPrecipitacao 
dados_daFunceme::getTipoPrecipitacao( unsigned int Ano, unsigned int Mes, 
									  unsigned int Dia, postoFunceme &Posto)
{
	unsigned int ano_comInfo=0;
	unsigned int mes_comInfo=0;

	if( Dia > 31 )
		return DIA_INVALIDO;

	if( Mes > 12 )
		return MES_INVALIDO;

	vector<indices_deChuva>::iterator icIter;
	for( icIter=Posto.Indices.begin(); icIter!=Posto.Indices.end(); ++icIter ){
		if( icIter->Ano == Ano ){
			ano_comInfo=1;
			if ( icIter->Mes == Mes ){
				mes_comInfo=1;
				vector<double>::iterator dIter = icIter->Precipitacoes.begin()+(Dia-1);

				//begin: Para debugar
				// cout << "Cidade:" << Posto.Cidade << "\n";
				// cout << "Posto:" << Posto.nomePosto << "\n";
				// cout << "Coordenada x: " << Posto.xCoord << "\n";
				// cout << "Coordenada y: " << Posto.yCoord << "\n";
				// cout << "Ano: " << icIter->Ano << "\n";
				// cout << "Mes: " << icIter->Mes << "\n";
				// cout << "Total: " << icIter->Total << "\n";
				// cout << "Dia: " << Dia << "\n";
				// cout << "Epsilon: " << Epsilon << "\n";
				// cout << "Precipitacao: " << *dIter << "\n";
				//end: Para Debugar

				if( fabs(*dIter - 888) < Epsilon )
					return DIA_INVALIDO;
				if( fabs(*dIter - 999) < Epsilon )
					return DIA_SEM_INFO;
				return INFORMADA;
				break;
			}
		}
	}

	if(!ano_comInfo) //Se passar daqui o mês não possui informação!
		return ANO_SEM_INFO;

	if(!mes_comInfo) //Chegando aqui não passa!
		return MES_SEM_INFO;
	
	return INDEFINIDA;//Essa situação não ocorre!
}

tipoPrecipitacao 
dados_daFunceme::getTipoPrecipitacao( unsigned int Ano, unsigned int Mes, 
									  unsigned int Dia, unsigned int Identidade)
{
	vector<postoFunceme>::iterator ptIter;
	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter )
		if( ptIter->Identidade == Identidade )
			return getTipoPrecipitacao( Ano, Mes, Dia, *ptIter );

	return ID_INVALIDO;
}

double dados_daFunceme::getValorPrecipitacao( unsigned int Ano, unsigned int Mes, 
											  unsigned int Dia, postoFunceme &Posto )
{
	vector<indices_deChuva>::iterator icIter;
	double valorPrecipitacao;

	for( icIter=Posto.Indices.begin(); icIter!=Posto.Indices.end(); ++icIter )
		if( icIter->Ano == Ano )
			if ( icIter->Mes == Mes )
				valorPrecipitacao = *(icIter->Precipitacoes.begin()+(Dia-1));

	return valorPrecipitacao;
}

double dados_daFunceme::getValorPrecipitacao( unsigned int Ano, unsigned int Mes, 
								 unsigned int Dia, unsigned int Identidade )
{
	vector<postoFunceme>::iterator ptIter;
	double valorPrecipitacao;

	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter )
		if( ptIter->Identidade == Identidade )
			valorPrecipitacao = getValorPrecipitacao( Ano, Mes, Dia, *ptIter );

	return valorPrecipitacao;
}

double dados_daFunceme::aproximarIndice( unsigned int Ano, unsigned int Mes, 
										 unsigned int Dia, double x, double y )
{
	vector<postoFunceme>::iterator ptIter, ptIterMenorDistancia;
	//Para guardar o quadrado da distancia.
	double menorDistancia, Distancia;

	ptIterMenorDistancia = postosFunceme.begin();
	menorDistancia = ( ptIterMenorDistancia->xCoord - x )*
		( ptIterMenorDistancia->xCoord - x ) +
		( ptIterMenorDistancia->yCoord - y )*
		( ptIterMenorDistancia->yCoord - y );

	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter ){
		Distancia = ( ptIter->xCoord - x )*( ptIter->xCoord - x ) +
			( ptIter->yCoord - y )*( ptIter->yCoord - y );
		if( Distancia < menorDistancia ){
			menorDistancia = Distancia;
			ptIterMenorDistancia = ptIter;
		}
	}

	cout << "Menor distancia: " << sqrt(menorDistancia) << "\n";
	cout << "Dobro da Menor distancia: " << 2*sqrt(menorDistancia) << "\n";

	// Verifica se as cooordenadas informadas
	// são as coordenadas de um pluviômetro!
	if( sqrt(menorDistancia) < Epsilon ){
		cout << "As coordenadas são de um polo!" << "\n";
		if( getTipoPrecipitacao( Ano, Mes, Dia, *ptIterMenorDistancia ) == INFORMADA )
			return getValorPrecipitacao( Ano, Mes, Dia, *ptIterMenorDistancia );
		else
			return 0;
	}

	double indiceAproximado;
	double somaPonderada=0;
	double somaPesos=0;

	cout << "As coordenadas não são de um polo!" << "\n";
	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter ){
		Distancia = ( ptIter->xCoord - x )*( ptIter->xCoord - x ) +
			( ptIter->yCoord - y )*( ptIter->yCoord - y );
		if( Distancia < 4*menorDistancia ){//Quadrado da Distancia
			cout << "\nDistancia ao posto " << ptIter->Identidade;
			cout << ": " << sqrt(Distancia) << "\n";
			if( getTipoPrecipitacao( Ano, Mes, Dia, *ptIter ) == INFORMADA ){
				somaPonderada = somaPonderada + 
					getValorPrecipitacao( Ano, Mes, Dia, *ptIter )/
					(Distancia*Distancia);
				somaPesos = somaPesos + 1/(Distancia*Distancia);
			}
		}
	}

	if( somaPesos )
		indiceAproximado = somaPonderada/somaPesos;
	else
		indiceAproximado = 0;

	return indiceAproximado;
}

//Retorna os postos usados no c\'alculo do \'indice de chuva
double dados_daFunceme::aproximarIndice( unsigned int Ano, unsigned int Mes, 
										 unsigned int Dia, double x, double y,
										 vector<chuva_ePosto> &Postos )
{
	vector<postoFunceme>::iterator ptIter, ptIterMenorDistancia;
	//Para guardar o quadrado da distancia.
	double menorDistancia, Distancia;
	chuva_ePosto tempCP;

	ptIterMenorDistancia = postosFunceme.begin();
	menorDistancia = ( ptIterMenorDistancia->xCoord - x )*
		( ptIterMenorDistancia->xCoord - x ) +
		( ptIterMenorDistancia->yCoord - y )*
		( ptIterMenorDistancia->yCoord - y );

	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter ){
		Distancia = ( ptIter->xCoord - x )*( ptIter->xCoord - x ) +
			( ptIter->yCoord - y )*( ptIter->yCoord - y );
		if( Distancia < menorDistancia ){
			menorDistancia = Distancia;
			ptIterMenorDistancia = ptIter;
		}
	}

	cout << "Menor distancia: " << sqrt(menorDistancia) << "\n";
	cout << "Dobro da Menor distancia: " << 2*sqrt(menorDistancia) << "\n";

	// Verifica se as cooordenadas informadas
	// são as coordenadas de um pluviômetro!
	if( sqrt(menorDistancia) < Epsilon ){
		cout << "As coordenadas são de um polo!" << "\n";
		tempCP.Ano = Ano;
		tempCP.Mes = Mes;
		tempCP.Dia = Dia;
		tempCP.Identidade = ptIterMenorDistancia->Identidade;
		tempCP.Cidade = ptIterMenorDistancia->Cidade;
		tempCP.nomePosto = ptIterMenorDistancia->nomePosto;
		tempCP.Distancia = sqrt(menorDistancia);
		tempCP.Tipo = getTipoPrecipitacao( Ano, Mes, Dia, *ptIterMenorDistancia );
		tempCP.Valor = getValorPrecipitacao( Ano, Mes, Dia, *ptIterMenorDistancia );
		Postos.push_back( tempCP );
		if( tempCP.Tipo == INFORMADA ){
			return tempCP.Valor;
		}
		else
			return 0;
	}

	double indiceAproximado;
	double somaPonderada=0;
	double somaPesos=0;

	cout << "As coordenadas não são de um polo!" << "\n";
	for( ptIter=postosFunceme.begin(); ptIter!=postosFunceme.end(); ++ptIter ){
		Distancia = ( ptIter->xCoord - x )*( ptIter->xCoord - x ) +
			( ptIter->yCoord - y )*( ptIter->yCoord - y );
		if( Distancia < 4*menorDistancia ){//Quadrado da Distancia
			tempCP.Ano = Ano;
			tempCP.Mes = Mes;
			tempCP.Dia = Dia;
			tempCP.Identidade = ptIter->Identidade;
			tempCP.Cidade = ptIter->Cidade;
			tempCP.nomePosto = ptIter->nomePosto;
			tempCP.Distancia = sqrt(Distancia);
			tempCP.Tipo = getTipoPrecipitacao( Ano, Mes, Dia, *ptIter );
			tempCP.Valor = getValorPrecipitacao( Ano, Mes, Dia, *ptIter );
			Postos.push_back( tempCP );
			if( tempCP.Tipo == INFORMADA ){
				somaPonderada = somaPonderada + 
					tempCP.Valor / (Distancia*Distancia);
				somaPesos = somaPesos + 1/(Distancia*Distancia);
			}
		}
	}

	if( somaPesos )
		indiceAproximado = somaPonderada/somaPesos;
	else
		indiceAproximado = 0;

	return indiceAproximado;
}
