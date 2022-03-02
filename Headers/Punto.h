#ifndef PUNTO_H
#define PUNTO_H


class Punto
{
private:
    double x;
    double y;
public:
    explicit Punto(double = 0, double = 0);
    ~Punto() = default;
    Punto(const Punto&);
    Punto& operator=(const Punto&);

    Punto* clone() const;

    double getX() const;
    double getY() const;
};

#endif // PUNTO_H
