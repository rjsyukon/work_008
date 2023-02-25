
#include "dados_daFunceme.hpp"
#include "indices_deChuva.hpp"
#include "postoFunceme.hpp"

#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

int exec1( int argc, char **argv )
{
	dados_daFunceme Funceme;
	unsigned int Dia, Mes, Ano, Identidade;
	Ano = atoi( argv[1] );
	Mes = atoi( argv[2] );
	Dia = atoi( argv[3] );
	Identidade = atoi( argv[4] );
	tipoPrecipitacao tp = 
		Funceme.getTipoPrecipitacao( Ano, Mes, Dia, Identidade );
	
	if( tp == ID_INVALIDO )
		cout << "Posto inexistente\n";

	if( tp	== ANO_SEM_INFO )
		cout << "Ano sem informaçao\n";

	if( tp	== MES_SEM_INFO )
		cout << "Mes sem informaçao\n";

	if( tp	== DIA_SEM_INFO )
		cout << "Dia sem informaçao\n";

	if( tp	== DIA_INVALIDO )
		cout << "Dia Inválido\n";

	if( tp	== MES_INVALIDO )
		cout << "Mes Inválido\n";

	if( tp	== INFORMADA ){
		cout << "Precipitação Informada\n";
		cout << "Valor: ";
		cout << Funceme.getValorPrecipitacao( Ano, Mes, Dia, Identidade ) << "\n";
	}
	return 0;
}

int exec2( int argc, char **argv )
{
	dados_daFunceme Funceme;
	unsigned int Dia, Mes, Ano;
	double x, y;
	double valorPrecipitacao;
	Ano = atoi( argv[1] );
	Mes = atoi( argv[2] );
	Dia = atoi( argv[3] );
	x = atof( argv[4] );
	y = atof( argv[5] );	

	valorPrecipitacao = Funceme.aproximarIndice( Ano, Mes, Dia, x, y );

	cout << "\nValor Aproximado: " << valorPrecipitacao << "\n\n";

	return 0;
}

int exec3( int argc, char **argv )
{
	cout << ANO_SEM_INFO << "\n";
	cout << MES_SEM_INFO << "\n";
	cout << DIA_SEM_INFO << "\n";
	cout << DIA_INVALIDO << "\n";
	cout << MES_INVALIDO << "\n";
	cout << ID_INVALIDO << "\n";
	cout << INFORMADA << "\n";
	cout << INDEFINIDA << "\n";

	return 0;
}

int exec4( int argc, char **argv )
{
	map<tipoPrecipitacao, string> tipoInformacao;
	mapTipoPrecipitacao( tipoInformacao );

	dados_daFunceme Funceme;
	unsigned int Dia, Mes, Ano;
	double x, y;
	double valorPrecipitacao;
	Ano = atoi( argv[1] );
	Mes = atoi( argv[2] );
	Dia = atoi( argv[3] );
	x = atof( argv[4] );
	y = atof( argv[5] );
	vector<chuva_ePosto> Postos;

	valorPrecipitacao = Funceme.aproximarIndice( Ano, Mes, Dia, x, y, Postos );
	vector<chuva_ePosto>::iterator Iter;
	cout << "\nPostos na distancia desejada\n\n";
	for( Iter=Postos.begin(); Iter!=Postos.end(); ++Iter ){
		cout << "Cidade:" << Iter->Cidade << "\n";
		cout << "Posto:" << Iter->nomePosto << "\n";
		cout << "Identidade:" << Iter->Identidade << "\n";
		cout << "Distancia:" << Iter->Distancia << "\n";
		cout << "Ano: " << Iter->Ano << "\n";
		cout << "Mes: " << Iter->Mes << "\n";
		cout << "Dia: " << Iter->Dia << "\n";
		cout << "Tipo: " << tipoInformacao[Iter->Tipo] << "\n";
		if( Iter->Tipo == INFORMADA )
			cout << "Precipitacao: " << Iter->Valor << "\n";
		cout << "\n";
	}

	cout << "\nValor Aproximado: " << valorPrecipitacao << "\n\n";
	cout << endl;

	return 0;
}

int main( int argc, char **argv )
{
	exec4( argc, argv );

	return 0;
}
