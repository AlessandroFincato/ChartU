#include "Lineare.h"

Lineare::Lineare(std::string t, std::vector<std::string> l, std::vector<std::vector<double> > v) :
    Grafico(l,t), valori(v) {}

Lineare::Lineare(const Lineare &l) : valori(l.valori) {}

Lineare *Lineare::clone() const {
    return new Lineare(*this);
}

Lineare &Lineare::operator=(const Lineare &l) {
    if(this != &l)
        valori = l.valori;
    return *this;
}

void Lineare::addValue(unsigned int e, double nv) {
    if(e < valori.size()) {
        valori[e].push_back(nv);
    }
    else {
        //throw err: elemento non presente
    }
}

void Lineare::addValues(std::string ne, std::vector<double> ve) {
    addLegendVoice(ne);
    valori.push_back(ve);
}

void Lineare::addValuesLine(std::vector<double> nv) {
    if(nv.size() == valori.size()) {
        for(int i=0; i<valori.size(); i++)
            valori[i].push_back(nv[i]);
    }
    else {
        //#nuovi valori e #elementi non corrispondono
    }
}

void Lineare::changeValue(unsigned int e, unsigned int v, double nv) {
    if(e<valori.size()) {
        if(v<valori[e].size())
            valori[e][v] = nv;
        else {
            //throw err: riga non trovata
        }
    }
    else {
        //throw err: colonna non presente
    }
}

void Lineare::changeValues(unsigned int e, std::vector<double> nvs) {
    if(e < valori.size()) {
        valori[e] = nvs;
    }
    else {
        //throw err: elemento non presente
    }
}

void Lineare::changeAllValues(std::vector<std::vector<double> > new_vals) {
    valori = new_vals;
}

void Lineare::updateValues(unsigned int e, std::vector<double> nvs) {
    if(e < valori.size()) {
        if(nvs.size() == valori[e].size()){
            for(int i=0; i<valori[e].size(); i++) {
                if(valori[e][i] != nvs[i])
                    valori[e][i] = nvs[i];
            }
        }
        else {
            //throw err: lunghezze non corrispondono
        }
    }
    else {
        //throw err: elemento non presente
    }
}

void Lineare::updateAllValues(std::vector<std::vector<double> > up_vals) {
    if(up_vals.size() == valori.size()) {
        for(int i=0; i<valori.size(); i++) {
            if(up_vals[i].size() == valori[i].size()) {
                for(int j=0; j<valori[i].size(); j++) {
                    if(valori[i][j] != up_vals[i][j])
                        valori[i][j] = up_vals[i][j];
                }
            }
            else {
                //throw err: lunghezze colonna i non corrispondono
            }
        }
    }
    else {
        //throw err: #elementi(colonne) non corrispondono
    }
}
