#ifndef AREOGRAMMA_H
#define AREOGRAMMA_H

#include "Headers/Grafico.h"

class Areogramma : public Grafico {
    private:
        vector<double> valori;
    public:
        explicit Areogramma(string = "Areogramma",
                            vector<string> = vector<string>(),
                            vector<double> = vector<double>());
        Areogramma(const Areogramma&);
        Areogramma* clone() const;
        Areogramma& operator=(const Areogramma&);

        void addElement(string, Punto*);
        void addValue(string, Punto*);
        void changeElement(string, vector<Punto*>, string);
        void removeValues(int);
        void removeElement(string);

        void stampa();
};

#endif // AREOGRAMMA_H
