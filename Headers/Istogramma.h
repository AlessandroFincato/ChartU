#ifndef ISTOGRAMMA_H
#define ISTOGRAMMA_H

#include "Headers/Grafico.h"

class Istogramma : public Grafico {
private:
    string asse_y;
    vector<string> nome_gruppi; //numero dei ragruppamenti, asse x
    vector<vector<double>> valori;
public:
    explicit Istogramma(string = "Istogramma",
                        vector<string> = vector<string>(),
                        vector<string> = vector<string>(),
                        vector<vector<double>> = vector<vector<double>>(),
                        string = "");
    Istogramma(const Istogramma&);
    Istogramma* clone() const;
    Istogramma& operator=(const Istogramma&);

    void changeYAxes(string);

    string getAsseY() const;

    void addGroup(string);

    void addElement(string, Punto*);
    void addValue(string, Punto*);
    void changeElement(string, vector<Punto*>, string);
    void removeValues(int);
    void removeElement(string);

    void stampa();
};

#endif // ISTOGRAMMA_H
