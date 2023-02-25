
#ifndef _POSTOFUNCEME_HPP_
#define _POSTOFUNCEME_HPP_

#include <string>
#include <vector>
using namespace std;

#include "indices_deChuva.hpp"

class postoFunceme
{

public:
	postoFunceme();
	unsigned int Identidade;
	string Cidade;
	string nomePosto;
	double xCoord; 
	double yCoord;
	vector<indices_deChuva> Indices;

private:

protected:

};


#endif  // _POSTOFUNCEME_HPP_

