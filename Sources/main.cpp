#include "Headers/MainWidget.h"
#include "Headers/Controller.h"
#include "Headers/Model.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget v;
    Controller c;
    Model m;

    c.setModel(&m);
    c.setView(&v);
    v.setController(&c);

    v.show();

    return a.exec();
}
