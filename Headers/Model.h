#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include<iostream>

#include "Headers/Punto.h"

#include "Headers/Areogramma.h"
#include "Headers/Cartesiano.h"
#include "Headers/Istogramma.h"
#include "Headers/Grafico.h"

using namespace std;

class Model
{
private:
    Grafico* grafico_corrente;
public:
    Model();
    ~Model();

    //is
    bool isSetted() const;
    bool isAreogramma() const;
    bool isIstogramma() const;
    bool isCartesiano() const;

    //setter corrente
    void setAreogramma();
    void setCartesiano();
    void setIstogramma();

    //generali
    void changeTitle(string);
    void addLegendVoice(string);
    void changeLegendElement(string, string);
    void changeYAxes(string); //solo per Istogramma e Cartesiano

    void addElement(string, double = -1, double = -1);
    void addValue(string, double, double = -1);
    void changeElement(string, vector<vector<double>>, string = "");
    void removeValues(int);
    void removeElement(string);

    void stampa();

    //Specifici Cartesiano
    void changeXAxes(string);

    //Specifici Istogramma
    void addGroup(string);
};

#endif // MODEL_H
