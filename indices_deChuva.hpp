
#ifndef _INDICES_DECHUVA_HPP_
#define _INDICES_DECHUVA_HPP_

#include <vector>
using namespace std;

class indices_deChuva
{

public:
	indices_deChuva();
	unsigned int Ano;
	unsigned int Mes;
	double Total; //Soma das precipitacoes do mes!
	vector<double> Precipitacoes;

private:

protected:

};

#endif  // _INDICES_DECHUVA_HPP_

