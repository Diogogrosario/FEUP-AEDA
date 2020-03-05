#include "frota.h"
#include <string>

using namespace std;


void Frota::adicionaVeiculo(Veiculo *v1){
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const{
    return veiculos.size();
}

int Frota::menorAno() const{
    int menor=99999999;
    if(veiculos.size() ==0)
        return 0;
    for (int i=0;i<veiculos.size();i++)
    {
        if(veiculos.at(i)->getAno()<menor)
            menor = veiculos.at(i)->getAno();
    }
    return menor;
}

 ostream & operator<<(ostream & o, const Frota & f){
    for(int i = 0;i<f.veiculos.size();i++)
        f.veiculos.at(i)->info();
    return o;
}

vector<Veiculo *> Frota::operator () (int anoM) const{
    vector<Veiculo*> FrotaModified;
    for (int i=0;i<veiculos.size();i++){
        if (veiculos.at(i)->getAno() == anoM)
            FrotaModified.push_back(veiculos.at(i));
    }
    return FrotaModified;
}