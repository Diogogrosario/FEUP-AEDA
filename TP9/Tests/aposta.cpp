#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
    if(numeros.find(num) == numeros.end())
        return false;
	return true;
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    int counter= 0;
    for (auto it = valores.begin(); it != valores.end() &&  counter < n; it++)
        if (numeros.find(*it) == numeros.end()) {
            numeros.insert(*it);
            counter++;
        }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    int counter = 0;
    for(auto it = numeros.begin(); it != numeros.end(); it ++)
        if(sorteio.find(*it) != numeros.end())
            counter++;
    return counter;
}





