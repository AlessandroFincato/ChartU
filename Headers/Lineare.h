#ifndef LINEARE_H
#define LINEARE_H

#include "Grafico.h"

class Lineare : public Grafico {
private:
    std::vector<std::vector<double>> valori;
public:
    Lineare(std::string,std::vector<std::string>,std::vector<std::vector<double>>);
    Lineare(const Lineare&);
    Lineare *clone() const;
    Lineare& operator=(const Lineare&);

    void addValue(unsigned int,double);
    void addValues(std::string,std::vector<double>);
    void addValuesLine(std::vector<double>);

    void changeValue(unsigned int,unsigned int,double);
    void changeValues(unsigned int,std::vector<double>);
    void changeAllValues(std::vector<std::vector<double>>);

    //void updateValue(unsigned int, unsigned int,double); ha senso il singolo valore?
    void updateValues(unsigned int,std::vector<double>);
    void updateAllValues(std::vector<std::vector<double>>);
};

#endif // LINEARE_H
