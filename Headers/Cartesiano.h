#ifndef CARTESIANO_H
#define CARTESIANO_H

#include "Headers/Grafico.h"

class Cartesiano : public Grafico {
    private:
        string asse_x;
        string asse_y;
        vector<vector<Punto*>> valori;
    public:
        explicit Cartesiano(string = "Grafico Cartesiano",
                            vector<string> = vector<string>(),
                            vector<vector<Punto*>> = vector<vector<Punto*>>(),
                            string = "", string = "");
        Cartesiano(const Cartesiano&);
        Cartesiano* clone() const;
        Cartesiano& operator=(const Cartesiano&);

        string getXAxes() const;
        string getYAxes() const;

        void changeXAxes(string);
        void changeYAxes(string);

        void addElement(string, Punto *);
        void addValue(string, Punto *);
        void changeElement(string, vector<Punto*>, string);
        void removeValues(int);
        void removeElement(string);

        void stampa();
};

#endif // CARTESIANO_H
