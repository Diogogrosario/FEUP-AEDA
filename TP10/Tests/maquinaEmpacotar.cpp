#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


// a alterar
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
    int counter = 0;
    for(size_t i = 0 ;i < objs.size();i++){
        if(objs.at(i).getPeso() <= capacidadeCaixas){
            objetos.push(objs.at(i));
            objs.erase(objs.begin()+i);
            i--;
            counter++;
        }
    }
    return counter;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;
	HEAP_CAIXAS aux;
	while(!caixas.empty()){
	    if(caixas.top().getCargaLivre() >= obj.getPeso()){
	        cx = caixas.top();
            caixas.pop();
	        break;
	    }
	    else{
            aux.push(caixas.top());
            caixas.pop();
	    }

	}
	while(!aux.empty()){
	    caixas.push(aux.top());
	    aux.pop();
	}
	return cx;
}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {
    Caixa cx;
    while(!this->objetos.empty()){
        cx = procuraCaixa(const_cast<Objeto &> (objetos.top()));
        cx.addObjeto(const_cast<Objeto &> (objetos.top()));
        caixas.push(cx);
        objetos.pop();

    }
	return caixas.size();
}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    if(objetos.size() == 0) {
        return "Nao ha objetos!\n";
    }
    string ret = "";
    HEAP_OBJS aux = objetos;
    while(!aux.empty()) {
        ret += "O" + to_string(aux.top().getID()) + ": " + to_string(aux.top().getPeso());
        ret += "\n";
        aux.pop();
    }
	return ret;
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa cx;
	int size = 0;
	if(caixas.size() == 0)
	    throw MaquinaSemCaixas();
	HEAP_CAIXAS aux = caixas;
	while(!aux.empty()){
	    if(aux.top().getSize() > size){
	        cx = aux.top();
	        size = aux.top().getSize();
	    }
	    aux.pop();
	}
	return cx;
}



