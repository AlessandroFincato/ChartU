#include "Headers/Areogramma.h"

Areogramma::Areogramma(string t,
                       vector<string> l,
                       vector<double> v) :
    Grafico(t,l), valori(v) {}

Areogramma::Areogramma(const Areogramma& g) :
    Grafico(g), valori(g.valori) {}

Areogramma* Areogramma::clone() const {
    return new Areogramma(*this);
}

Areogramma& Areogramma::operator=(const Areogramma& gt) {
    if(this != &gt){
        Grafico::operator =(gt);
        valori = gt.valori;
    }

    return *this;
}

void Areogramma::addElement(string n, Punto* p){
    addLegendVoice(n); //potrebbe lanciare runtime_error
    valori.push_back(p ? p->getX() : 0);
}

void Areogramma::addValue(string s, Punto* p){
    if(isPresent(s))
        valori[getIndex(s)] = p->getX();
    else
        throw runtime_error("Elemento non presente");
}

void Areogramma::changeElement(string old_n, vector<Punto*> values, string new_n){
    if(isPresent(old_n)) {
        valori[getIndex(old_n)] = values[0]->getX();
        changeLegendElement(old_n,new_n);
    }
    else
        throw runtime_error("Elemento non presente");
}

void Areogramma::removeValues(int col) {
    for(unsigned int i = 0; i < valori.size(); i++) {
        valori[i] = 0;
    }
}

void Areogramma::removeElement(string nome) {
    auto it = valori.begin();
    for(int i = 0; i < getIndex(nome); i++)
        it++;
    valori.erase(it);
    removeLegendVoice(nome);
}

void Areogramma::stampa() {
    cout << "Titolo: " << getTitle() << endl;
    for(unsigned int i = 0; i<valori.size(); i++){
        cout << getLegendVoice(i) << ": " << valori[i] << endl;
    }
}
