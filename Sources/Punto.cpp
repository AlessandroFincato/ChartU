#include "Headers/Punto.h"

Punto::Punto(double v1, double v2) : x(v1), y(v2) {}

Punto::Punto(const Punto& p) : x(p.x), y(p.y) {}

Punto& Punto::operator=(const Punto& p) {
    if(this != &p) {
        x = p.x;
        y = p.y;
    }

    return *this;
}

Punto *Punto::clone() const {
    return new Punto(*this);
}

double Punto::getX() const {
    return x;
}

double Punto::getY() const {
    return y;
}
