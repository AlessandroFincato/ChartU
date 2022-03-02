#include "Headers/Istogramma.h"

Istogramma::Istogramma(string t,
                       vector<string> l,
                       vector<string> gruppi,
                       vector<vector<double>> val,
                       string y) :
    Grafico(t,l), asse_y(y), nome_gruppi(gruppi), valori(val) {}

Istogramma::Istogramma(const Istogramma& i) :
    Grafico(i), asse_y(i.asse_y), nome_gruppi(i.nome_gruppi), valori(i.valori) {}

Istogramma* Istogramma::clone() const {
    return new Istogramma(*this);
}

Istogramma& Istogramma::operator=(const Istogramma& i) {
    if(this != &i) {
        Grafico::operator =(i);
        nome_gruppi = i.nome_gruppi;
        valori = i.valori;
        asse_y = i.asse_y;
    }
    return *this;
}

void Istogramma::changeYAxes(string s) {
    asse_y = s;
}

string Istogramma::getAsseY() const {
    return asse_y;
}

void Istogramma::addGroup(string s) {
    bool presente = false;

    for(unsigned int i = 0; i < nome_gruppi.size() && !presente; i++) {
        if(nome_gruppi[i] == s)
            presente = true;
    }

    if(!presente)
        nome_gruppi.push_back(s);
    else
        throw runtime_error("Nome del gruppo già presente");
}

void Istogramma::addElement(string n, Punto* fv) {
    addLegendVoice(n); //potrebbe lanciare runtime_error
    vector<double> aux;
    if(fv)
        aux.push_back(fv->getX());
    valori.push_back(aux);
}

void Istogramma::addValue(string n, Punto* fv) {
    if(isPresent(n))
        valori[getIndex(n)].push_back(fv->getX());
    else {
        throw runtime_error("Elemento non presente");
    }
}

void Istogramma::changeElement(string old_n, vector<Punto*> vs, string new_n) {
    if(isPresent(old_n)) {
        for(unsigned int i=0; i<valori[getIndex(old_n)].size(); i++)
            valori[getIndex(old_n)][i] = vs[i]->getX();

        for(unsigned int i = valori[getIndex(old_n)].size(); i<vs.size(); i++)
            valori[getIndex(old_n)].push_back(vs[i]->getX());

        changeLegendElement(old_n,new_n);
    } else {
        throw runtime_error("Elemento non presente");
    }
}

void Istogramma::removeValues(int col) {
    for(unsigned int i=0; i<valori.size(); i++) {
        if(valori[i].size() >= col) {
            auto it = valori[i].begin();
            for(int j=0; j<col; j++)
                it++;
            valori[i].erase(it);
        }
    }

    auto it = nome_gruppi.begin();
    for(int i = 0; i < col; i++)
        it++;
    nome_gruppi.erase(it);
}

void Istogramma::removeElement(string nome) {
    auto it = valori.begin();
    for(int i = 0; i < getIndex(nome); i++)
        it++;
    valori.erase(it);
    removeLegendVoice(nome);
}

void Istogramma::stampa() {
    cout << "Titolo: " << getTitle() << endl;
    cout << "asseY: " << getAsseY() << endl;
    for(unsigned int r = 0; r < valori.size(); r++) {
        cout << getLegendVoice(r) << ":" <<endl;
        for(unsigned int c = 0; c < valori[r].size(); c++) {
            cout << "    " << nome_gruppi[c] << ": " << valori[r][c] << endl;
        }
    }
}
