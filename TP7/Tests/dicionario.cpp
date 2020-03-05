#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
    return palavra < ps1.palavra;
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich)
{
    int counter  = 0;
    string linha,palavra;
    while(getline(fich,linha)){
        switch(counter){
            case 0:
                palavra = linha;
                counter++;
                break;
            case 1:
                palavras.insert((PalavraSignificado(palavra,linha)));

                counter = 0;
                break;
        }
    }
}

//a alterar
string Dicionario::consulta(string palavra) const
{
    return "";
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    return true;
}

//a alterar
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    while(!it.isAtEnd()) {
        cout << it.retrieve().getPalavra() << endl;
        cout << it.retrieve().getSignificado()  << endl;
        it.advance();
    }
    return;
}

