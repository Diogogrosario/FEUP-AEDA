#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};


template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }

// excecao ArestaRepetido
template<class N>
class ArestaRepetido
{
public:
    N destino;
    N inicio;
    ArestaRepetido(N ini, N dest) {
        destino = dest;
        inicio = ini;
    }
};
template<class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetido<N> &aresta)
{ out << "Aresta repetida: " << aresta.inicio << " , " <<aresta.destino; return out; }

// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template<class N, class A>
Grafo<N, A>::Grafo()
{
    nos = {};
}

template<class N, class A>
Grafo<N, A>::~Grafo() {
    nos.clear();
}

template<class N, class A>
int Grafo<N, A>::numNos(void) const {
    return nos.size();
}

template<class N, class A>
int Grafo<N, A>::numArestas(void) const {
    int nArestas=0;
    for (int i = 0;i<nos.size();i++){
        nArestas += nos.at(i)->arestas.size();
    }
    return nArestas;
}

template<class N, class A>
Grafo<N,A> &Grafo<N, A>::inserirNo(const N &dados) {
    for(int i = 0;i<nos.size();i++)
    {
        if (nos.at(i)->info == dados){
            NoRepetido<N> noRepetido(dados);
            throw noRepetido;
        }

    }
    No<N,A> *pointerNo = new No<N,A>(dados);
    nos.push_back(pointerNo);
    return *this;
}

template<class N, class A>
Grafo<N,A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    bool inicialExistente = false;
    bool finalExistente = false;
    int index;
    for(int i = 0;i<nos.size();i++)
    {
        if (nos.at(i)->info == inicio)
        {
            inicialExistente = true;
            index = i;
        }
    }
    if (!inicialExistente)
    {
        NoInexistente<N> noInexistente(inicio);
        throw noInexistente;
    }
    for(int j = 0;j<nos.at(index)->arestas.size();j++){
            if(nos.at(index)->arestas.at(j).destino->info == fim)
                finalExistente = true;
        }
    if (finalExistente){
        ArestaRepetido<N> arestaRepetido(inicio,fim);
        throw arestaRepetido;
    }
    No<N,A> *pointerNo = new No<N,A>(fim);
    Aresta<N,A> addAresta(pointerNo,val);
    nos.at(index)->arestas.push_back(addAresta);
    return *this;
}
