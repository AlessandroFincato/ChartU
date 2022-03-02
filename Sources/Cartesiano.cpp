#include "Headers/Cartesiano.h"

Cartesiano::Cartesiano(string t, vector<string> l,
                       vector<vector<Punto*>> v,
                       string x, string y) :
        Grafico(t,l), asse_x(x), asse_y(y), valori(v) {}

Cartesiano::Cartesiano(const Cartesiano& c) :
    Grafico(c), asse_x(c.asse_x), asse_y(c.asse_y), valori(c.valori) {}

Cartesiano* Cartesiano::clone() const {
    return new Cartesiano(*this);
}

Cartesiano& Cartesiano::operator=(const Cartesiano& c) {
    if(this != &c) {
        Grafico::operator =(c);
        asse_x = c.asse_x;
        asse_y = c.asse_y;
        valori = c.valori;
    }
    return *this;
}

string Cartesiano::getXAxes() const {
    return asse_x;
}

string Cartesiano::getYAxes() const {
    return asse_y;
}

void Cartesiano::changeXAxes(string s) {
    asse_x = s;
}

void Cartesiano::changeYAxes(string s) {
    asse_y = s;
}

void Cartesiano::addElement(string n, Punto* p) {
    addLegendVoice(n); //potrebbe lanciare runtime_error
    vector<Punto*> aux;
    if(p)
        aux.push_back(p->clone());
    valori.push_back(aux);
}

void Cartesiano::addValue(string n, Punto* p) {
    if(isPresent(n))
        valori[getIndex(n)].push_back((p->clone()));
    else {
        throw runtime_error("Elemento non presente");
    }
}

void Cartesiano::changeElement(string old_n, vector<Punto*> vs, string new_n) {
    if(isPresent(old_n)) {
        for(unsigned int i=0; i<valori[getIndex(old_n)].size(); i++)
            valori[getIndex(old_n)][i] = vs[i]->clone();

        for(unsigned int i=valori[getIndex(old_n)].size(); i<vs.size(); i++)
            valori[getIndex(old_n)].push_back(vs[i]->clone());

        changeLegendElement(old_n, new_n);
    }
    else {
        throw runtime_error("Elemento non presente");
    }
}

void Cartesiano::removeValues(int col) {
    for(unsigned int i=0; i<valori.size(); i++) {
        if(valori[i].size() >= col) {
            auto it = valori[i].begin();
            for(int j=0; j<col; j++)
                it++;
            valori[i].erase(it);
        }
    }
}

void Cartesiano::removeElement(string nome) {
    auto it = valori.begin();
    for(int i = 0; i < getIndex(nome); i++)
        it++;
    valori.erase(it);
    removeLegendVoice(nome);
}

void Cartesiano::stampa() {
    cout << "Titolo: " << getTitle() << endl;
    cout << "Asse_x: " << getXAxes() << endl;
    cout << "Asse_y: " << getYAxes() << endl;
    for(unsigned int r = 0; r < valori.size(); r++) {
        cout << getLegendVoice(r) << ": " << endl;
        for(unsigned int c = 0; c < valori[r].size(); c++) {
            cout << "    x: " << valori[r][c]->getX() << "  y: " << valori[r][c]->getY() << endl;
        }
    }
}
