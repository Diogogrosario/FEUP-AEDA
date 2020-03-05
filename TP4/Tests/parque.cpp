#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;



ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    vector <string> nomes;
    for(int i = 0; i<clientes.size();i++)
        nomes.push_back(clientes.at(i).nome);
    return sequentialSearch(nomes,nome);
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int i = posicaoCliente(nome);
    if(i == -1)
        throw ClienteNaoExistente(nome);
    return clientes[i].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
    reverse(clientes.begin(),clientes.end());
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    vector<string>nomes;
    vector <InfoCartao> aux;
    for(int i = 0;i<clientes.size();i++)
        nomes.push_back(clientes[i].nome);
    insertionSort(nomes);
    for(int i = 0;i<nomes.size();i++){
        for (int j = 0; j<nomes.size();j++)
            if(nomes[i] == clientes[j].nome)
                aux.push_back(clientes[j]);
    }
    clientes = aux;
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    vector<string> nomes;
    vector <InfoCartao>aux;
    for(int i = 0; i< clientes.size();i++){
        if(clientes[i].frequencia>=n1 and clientes[i].frequencia<=n2)
            aux.push_back(clientes[i]);
    }
    insertionSort(aux);
    reverse(aux.begin(),aux.end());
    for (int i = 0;i<aux.size();i++)
        nomes.push_back(aux[i].nome);
    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    return os;
}

bool InfoCartao::operator<(const InfoCartao &right) const{
    if(this->frequencia<right.frequencia)
        return true;
    else if(this->frequencia==right.frequencia) {
        if (this->nome > right.nome)
            return true;
    }
    return false;
}

// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    return info;
}

ClienteNaoExistente::ClienteNaoExistente(string nome){
    nomeCliente = nome;
}

string ClienteNaoExistente::getNome(){
    return nomeCliente;
}