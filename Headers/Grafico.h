#ifndef GRAFICO_H
#define GRAFICO_H

#include "Headers/Punto.h"

#include<vector>
#include<string>

#include<iostream>

using namespace std;

class Grafico {
    private:
        string titolo;
        vector<string> legenda; //contiene i nomi degli elementi che compongono il grafico
    public:
        explicit Grafico(string, vector<string>);
        //quando creo un grafico ho sicuramente almeno un elemento
        //quindi ho sicuramente almeno una voce nella legenda
        Grafico(const Grafico&);
        virtual ~Grafico() = default;
        virtual Grafico* clone() const = 0;
        Grafico& operator=(const Grafico&);

        void addLegendVoice(string);
        void removeLegendVoice(string);

        bool isPresent(string) const;
        int getIndex(string) const;
        string getLegendVoice(int) const;
        string getTitle() const;

        void changeTitle(string);
        void changeLegendElement(string, string = "");

        virtual void addElement(string, Punto* = nullptr) = 0;
        virtual void addValue(string, Punto*) = 0;
        virtual void changeElement(string, vector<Punto*>, string = "") = 0;
        virtual void removeValues(int = 0) = 0;
        virtual void removeElement(string = "") = 0;

        virtual void stampa() = 0;
};

#endif // GRAFICO_H
