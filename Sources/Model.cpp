#include "Headers/Model.h"

Model::Model() : grafico_corrente(nullptr) {}

Model::~Model() {}

bool Model::isSetted() const {
    return grafico_corrente ? true : false;
}

bool Model::isAreogramma() const {
    return dynamic_cast<Areogramma*>(grafico_corrente);
}

bool Model::isIstogramma() const {
    return dynamic_cast<Istogramma*>(grafico_corrente);
}

bool Model::isCartesiano() const {
    return dynamic_cast<Cartesiano*>(grafico_corrente);
}

void Model::setAreogramma() {
    grafico_corrente = new Areogramma();
}

void Model::setCartesiano() {
    grafico_corrente = new Cartesiano();
}

void Model::setIstogramma() {
    grafico_corrente = new Istogramma();
}

void Model::changeTitle(string s ) {
    if(grafico_corrente)
        grafico_corrente->changeTitle(s);
}

void Model::addLegendVoice(string s) {
    grafico_corrente->addLegendVoice(s);
}

void Model::changeLegendElement(string old_n, string new_n) {
    grafico_corrente->changeLegendElement(old_n, new_n);
}

void Model::addElement(string s, double x, double y) {
    Punto* p;
    if(x == -1)
        p = nullptr;
    else
        p = new Punto(x, (y==-1? 0 : y) );

    grafico_corrente->addElement(s,p);
}

void Model::addValue(string s, double x, double y) {
    Punto* p = new Punto(x, (y==-1? 0 : y) );

    grafico_corrente->addValue(s,p);
}

void Model::changeElement(string old_n, vector<vector<double>> vs, string new_n) {
    vector<Punto*> v;

    for(unsigned int i = 0; i < vs[0].size(); i++) {
        Punto* aux = new Punto(vs[0][i], vs[1][i]);
        v.push_back(aux);
    }

    grafico_corrente->changeElement(old_n, v, new_n);
}

void Model::removeValues(int col) {
    grafico_corrente->removeValues(col);
}

void Model::removeElement(string nome_elemento) {
    grafico_corrente->removeElement(nome_elemento);
}

void Model::stampa()
{
    grafico_corrente->stampa();
}

void Model::changeXAxes(string s) {
    dynamic_cast<Cartesiano*>(grafico_corrente)->changeXAxes(s);
}

void Model::changeYAxes(string s) {
    Cartesiano* p = dynamic_cast<Cartesiano*>(grafico_corrente);
    Istogramma* q = dynamic_cast<Istogramma*>(grafico_corrente);

    if(p)
        p->changeYAxes(s);
    else if (q)
        q->changeYAxes(s);
}

void Model::addGroup(string s) {
    dynamic_cast<Istogramma*>(grafico_corrente)->addGroup(s);
}
