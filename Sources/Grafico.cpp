#include "Headers/Grafico.h"

Grafico::Grafico(string t, vector<string> l) :
    titolo(t), legenda(l) {}

Grafico::Grafico(const Grafico& g) :
    titolo(g.titolo), legenda(g.legenda) {}

Grafico& Grafico::operator=(const Grafico &g) {
    if(this != &g) {
        titolo = g.titolo;
        legenda = g.legenda;
    }
    return *this;
}

void Grafico::addLegendVoice(string new_l){
    if(!isPresent(new_l)) {
        legenda.push_back(new_l);
    }
    else
        throw runtime_error("Nome già presetne,\ncambiarlo.");
}

void Grafico::removeLegendVoice(string nome) {
    if(nome != "") {
        vector<string>::iterator it = legenda.begin();
        for(unsigned int i = 0; i < legenda.size(); i++) {
            if( legenda[i] == nome)
                legenda.erase(it);
            it++;
        }
    }
}

bool Grafico::isPresent(string n) const {
    for(auto l : legenda) {
        if(l == n)
            return true;
    }
    return false;
}

int Grafico::getIndex(string n) const {
    for(unsigned int i=0; i<legenda.size(); i++) {
        if(legenda[i] == n)
            return i;
    }
    return -1;
}

string Grafico::getLegendVoice(int i) const {
    return legenda[i];
}

string Grafico::getTitle() const {
    return titolo;
}

void Grafico::changeTitle(string t) {
    titolo = t;
}

void Grafico::changeLegendElement(string old_n, string new_n) {
    legenda[getIndex(old_n)] = new_n == "" ? old_n : new_n;
}
