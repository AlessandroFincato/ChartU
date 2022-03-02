#include "Headers/Controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {}

Controller::~Controller() {}

void Controller::setModel(Model *m) {
    model = m;
}

void Controller::setView(MainWidget *v) {
    view = v;
}

//------SEGNALI------

void Controller::saveCurrent() {
    if(model->isSetted()) {
        update();

        QDomDocument document;
        QDomElement grafico = document.createElement("Grafico");
        document.appendChild(grafico);

        //aggiungo le info del grafico
        if(model->isAreogramma())
            grafico.setAttribute("Tipo", "Areogramma");
        else if(model->isIstogramma())
            grafico.setAttribute("Tipo", "Istogramma");
        else
            grafico.setAttribute("Tipo", "Cartesiano");

        grafico.setAttribute("Titolo", view->getChartTitle());

        if(!model->isAreogramma()) {
            if(model->isCartesiano())
                grafico.setAttribute("Asse_x", view->getXLabel());
            grafico.setAttribute("Asse_y", view->getYLabel());
        }

        //aggiungo i vari elementi con i rispettivi valori
        int row_count = view->getTableRowsCount();
        int col_count = view->getTableColsCount();
        for(int row = 0; row < row_count; row++) {
            QDomElement elemento = document.createElement(view->getTableVHeader(row));
            for(int col = 0; col < col_count; col++) {
                QDomElement punto = document.createElement("punto_" + QString::number(col));
                punto.setAttribute("x", QString::number(view->getTableValue(row,col)).replace(',','.'));
                punto.setAttribute("y", view->getTableHHeader(col));
                elemento.appendChild(punto);
            }
            grafico.appendChild(elemento);
        }

        try{
            QString path = view->getSavePosition("Seleziona la cartella dove salvare il file");
            QFile file(path + ".xml");
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << document.toString();
                file.close();
            }
        }
        catch(std::runtime_error exc) {
            view->showWarning(exc.what());
        }
    }
    else
        view->showWarning("Creare un grafico prima.");
}

void Controller::loadExisting() {
    try {
        QDomDocument document;

        QString path_file = view->getFile("Seleziona il file da caricare");
        QFile file(path_file);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            document.setContent(&file);
            file.close();
        }

        clearView();

        QDomElement root = document.firstChildElement();

        if(root.attribute("Tipo") == "Areogramma")
            setAreogramma();
        else if(root.attribute("Tipo") == "Istogramma")
            setIstogramma();
        else
            setCartesiano();

        setChartTitle(root.attribute("Titolo"));

        QDomNodeList elementi = root.childNodes();
        for(int row = 0; row < elementi.size(); row++) {
            QDomNode elemento = elementi.at(row);
            insertRow(elemento.nodeName());
            QDomNodeList punti = elemento.childNodes();
            for(int col = 0; col < punti.size(); col++) {
                QDomNode punto = punti.at(col);
                QDomNamedNodeMap attributi = punto.attributes();
                if(row==0 && !model->isAreogramma()){
                    QDomAttr y = attributi.namedItem("y").toAttr();
                    insertColumn(y.value());
                }
                QDomAttr x = attributi.namedItem("x").toAttr();
                addValue(row, col, (x.value()).toDouble());
                view->addTableValue(row, col, x.value());
            }
        }

        if(!model->isAreogramma()) {
            if(model->isCartesiano()) {
                view->setXLabel(root.attribute("Asse_x"));
                view->setYLabel(root.attribute("Asse_y"));
                view->updateCartAxes();
            }
            else {
                view->setYLabel(root.attribute("Asse_y"));
                view->updateIstoAxes();
            }
            model->changeYAxes(view->getYLabel().toStdString());
        }

        update();
    }
    catch (std::runtime_error exc) {
        view->showWarning(exc.what());
    }
}

void Controller::clearView() {
    view->clearTable();
    view->clearChart();
}

void Controller::setAreogramma() {
    model->setAreogramma();
    view->setAreoTable();
}

void Controller::setIstogramma() {
    model->setIstogramma();
    view->clearTable();
}

void Controller::setCartesiano() {
    model->setCartesiano();
    view->clearTable();
}

void Controller::setChartTitle(QString title) {
    model->changeTitle(title == "" ? view->getChartTitle().toStdString() : title.toStdString());
    view->setTitle(title);
}

void Controller::insertRow(QString nome_riga) {
    if(model->isSetted()) {
        try {
            model->addElement(nome_riga == "" ? view->getNewRowHeader().toStdString() : nome_riga.toStdString());

            view->addTableRow(nome_riga);

            if(model->isAreogramma())
                view->addAreoElement(nome_riga);
            else if (model->isIstogramma())
                view->addIstoElement(nome_riga);
            else //Cartesiano
                view->addCartElement(nome_riga);
        }
        catch(std::runtime_error exc) {
            view->showWarning(exc.what());
        }
    }
    else
        view->showWarning("Creare un grafico prima.");
}

void Controller::insertColumn(QString nome_colonna) {
    if(model->isSetted()) {
        if(model->isAreogramma()) {
            view->showWarning("Impossibile aggiungere una colonna\nil tipo di grafico non supporta l'operazione.");
        }
        else { //Cartesiano || Istogramma
            if(model->isIstogramma()) {
                try {
                    model->addGroup(nome_colonna == "" ? view->getNewColHeader().toStdString() : nome_colonna.toStdString());
                    view->addTableColumn(nome_colonna);
                }
                catch(std::runtime_error exc) {
                    view->showWarning(exc.what());
                }
            }

            if(model->isCartesiano()) {
                if(nome_colonna == "" && view->getTableColsCount() >= 1) {
                    double nuovo_valore = (view->getNewColHeader().replace(',','.')).toDouble();
                    double max_colonna = (view->getTableHHeader(view->getTableColsCount()-1).replace(',','.')).toDouble();
                    if(nuovo_valore <= max_colonna)
                        view->showWarning("Impossibile aggiungere una colonna\nil valore precede quello dell'ultima colonna inserita");
                    else
                        view->addTableColumn(nome_colonna);
                }
                else
                    view->addTableColumn(nome_colonna);
            }
        }
    }
    else
        view->showWarning("Creare un grafico prima.");
}

void Controller::addValue(int row, int col, double value) {
    if(model->isAreogramma()){
        view->addAreoValue(row,value);
    }
    else if(model->isIstogramma()) {
        view->addIstoValue(row,col,value);
    }
    else {//Cartesiano
        view->addCartValue(row,col,value);
    }
}

void Controller::addXLabel() {
    if(model->isSetted()){
        if(model->isCartesiano()) {
            view->updateCartAxes();
            model->changeXAxes(view->getXLabel().toStdString());

        }
        else
            view->showWarning("nome non inserito.");
    }
    else
        view->showWarning("Creare un grafico prima.");
}

void Controller::addYLabel() {
    if(model->isSetted()) {
        if(model->isAreogramma())
            view->showWarning("nome non inserito.\nIl grafico non ha assi");
        else {
            if(model->isIstogramma())
                view->updateIstoAxes();
            else
                view->updateCartAxes();

            model->changeYAxes(view->getYLabel().toStdString());
        }
    }
    else
        view->showWarning("Creare un grafico prima.");
}

void Controller::removeColumn() {
    if(view->getTableColsCount() > 0){
        if(model->isAreogramma())
            view->showWarning("Operazione non disponiblie\nper questo dipo di grafico");
        else {
            view->removeTableColumn();

            if(model->isIstogramma())
                view->removeIstoValue();
            else
                view->removeCartValue();

            model->removeValues(view->getSelectedColumn());
        }
    }
    else
        view->showWarning("Nessuna colonna da eliminare");
}

void Controller::removeRow() {
    if(view->getTableRowsCount() > 0) {
        if(model->isAreogramma())
            view->removeAreoElement();
        else if(model->isIstogramma())
            view->removeIstoElement();
        else
            view->removeCartElement();
        model->removeElement(view->getTableVHeader(view->getSelectedRow()).toStdString());
        view->removeTableRow();
    }
    else
        view->showWarning("Nessuna riga da eliminare");
}

void Controller::update() {
    view->updateChart();
    if(model->isIstogramma())
        view->updateIstoAxes();
    else if(model->isCartesiano())
        view->updateCartAxes();

    vector<double> x;
    vector<double> y;
    vector<vector<double>> v;
    for(int row = 0; row < view->getTableRowsCount(); row++) {
        v.clear(); x.clear(); y.clear();
        for(int col = 0; col < view->getTableColsCount(); col++) {
            x.push_back(view->getTableValue(row,col));
            y.push_back(view->getTableHHeader(col).toDouble());
        }
        v.push_back(x);
        v.push_back(y);
        try {
            model->changeElement(view->getTableVHeader(row).toStdString(), v);
        }
        catch (std::runtime_error exc) {
            view->showWarning(exc.what());
        }
    }
}

void Controller::stampa() {
    if(model->isSetted())
        model->stampa();
    else
        view->showWarning("Creare un grafico prima.");
}

void Controller::warningNew() {
    view->showWarning("Nessun grafico creato,\noperazione annullta");
}

void Controller::warningNewRow() {
    view->showWarning("Nessuna riga creata,\ninserimento annullato");
}

void Controller::warningNewColumn() {
    view->showWarning("Nessuna colonna creata,\ninserimento annullato");
}

void Controller::warningAx() {
    view->showWarning("Nessun nome definito,\ninserimento annullato");
}

void Controller::warningRemoveColumn() {
    view->showWarning("Nessuna colonna rimossa,\nselezione annullata");
}

void Controller::warningRemoveRow() {
    view->showWarning("Nessuna riga rimossa,\nselezione annullata");
}
