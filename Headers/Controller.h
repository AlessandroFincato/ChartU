#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<QtXml>

#include "Headers/Model.h"
#include "Headers/MainWidget.h"

class Controller : public QObject
{
    Q_OBJECT
private:
    MainWidget* view;
    Model* model;
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void setModel(Model *);
    void setView(MainWidget *);

signals:

public slots:
    void saveCurrent();
    void loadExisting();

    void clearView();
    void setAreogramma();
    void setIstogramma();
    void setCartesiano();
    void setChartTitle(QString = "");

    void insertRow(QString = "");
    void insertColumn(QString = "");
    void addValue(int,int,double = -1);
    void addXLabel();
    void addYLabel();

    void removeColumn();
    void removeRow();

    void update();
    void stampa();

    void warningNew();
    void warningNewRow();
    void warningNewColumn();
    void warningAx();
    void warningRemoveColumn();
    void warningRemoveRow();
};

#endif // CONTROLLER_H
