 #include "Headers/MainWidget.h"
#include "Headers/Controller.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();

    addMenu(layout);

    chart = new QChart();
    chart_view = new QChartView(chart);
    chart_view->setRenderHint(QPainter::Antialiasing);
    table = new QTableWidget();

    QHBoxLayout* central_layout = new QHBoxLayout();
    central_layout->addWidget(table);
    central_layout->addWidget(chart_view);

    layout->addLayout(central_layout);

    layout->setSpacing(5);
    setLayout(layout);
    resize(QSize(1024, 720));
}

MainWidget::~MainWidget() {}

void MainWidget::setController(Controller *c) {
    controller = c;

    connect(table, SIGNAL(cellChanged(int,int)), controller, SLOT(addValue(int,int)));

    connect(file->actions()[1], SIGNAL(triggered(bool)), controller, SLOT(loadExisting()));
    connect(file->actions()[2], SIGNAL(triggered(bool)), controller, SLOT(saveCurrent()));
    connect(file->actions()[4], SIGNAL(triggered(bool)), controller, SLOT(stampa()));

    connect(opzioni->actions()[6], SIGNAL(triggered(bool)), controller, SLOT(update()));
}

void MainWidget::setTitle(QString title) {
    chart->setTitle(title == "" ? chart_title->text() : title);
}

void MainWidget::setXLabel(QString s) {
    XAxLabel->setText(s);
}

void MainWidget::setYLabel(QString s) {
    YAxLabel->setText(s);
}

void MainWidget::setAreoTable() {
    table->clear();
    hTableHeader.clear();
    vTableHeader.clear();

    table->setColumnCount(1);
    table->setRowCount(0);

    hTableHeader.append("Valore");
    table->setHorizontalHeaderLabels(hTableHeader);
}

void MainWidget::clearTable() {
    table->clear();
    hTableHeader.clear();
    vTableHeader.clear();

    table->setColumnCount(0);
    table->setRowCount(0);
}

void MainWidget::addMenu(QLayout *ly) {
    menuBar = new QMenuBar(this);

    file = new QMenu("File", menuBar); menuBar->addMenu(file);
    opzioni = new QMenu("Opzioni", menuBar); menuBar->addMenu(opzioni);

    file->addAction(new QAction("Nuovo grafico", file));
    file->addAction(new QAction("Carica grafico", file));
    file->addAction(new QAction("Salva grafico", file));
    file->addAction(new QAction("Chiudi finestra", file));
    file->addAction(new QAction("stampa", file));

    opzioni->addAction(new QAction("inserisci riga", opzioni));
    opzioni->addAction(new QAction("inserisci colonna", opzioni));
    opzioni->addAction(new QAction("rimuovi riga", opzioni));
    opzioni->addAction(new QAction("rimuovi colonna", opzioni));
    opzioni->addAction(new QAction("inserisci nome asse x", opzioni));
    opzioni->addAction(new QAction("inserisci nome asse y", opzioni));
    opzioni->addAction(new QAction("aggiorna grafico", opzioni));

    connect(file->actions()[0], SIGNAL(triggered(bool)), this, SLOT(warningNew()));
    connect(file->actions()[3], SIGNAL(triggered(bool)), this, SLOT(close()));

    connect(opzioni->actions()[0], SIGNAL(triggered(bool)), this, SLOT(addRow()));
    connect(opzioni->actions()[1], SIGNAL(triggered(bool)), this, SLOT(addColumn()));
    connect(opzioni->actions()[2], SIGNAL(triggered(bool)), this, SLOT(removeRow()));
    connect(opzioni->actions()[3], SIGNAL(triggered(bool)), this, SLOT(removeColumn()));
    connect(opzioni->actions()[4], SIGNAL(triggered(bool)), this, SLOT(addXAxisLabel()));
    connect(opzioni->actions()[5], SIGNAL(triggered(bool)), this, SLOT(addYAxisLabel()));

    ly->addWidget(menuBar);
}

void MainWidget::addTableRow(QString nome) {
    vTableHeader.push_back(nome == "" ? newRowHeader->text() : nome);
    table->setRowCount(table->rowCount()+1);
    table->setVerticalHeaderLabels(vTableHeader);
}

void MainWidget::addAreoElement(QString nome) {
    QPieSlice *slice = new QPieSlice();
    slice->setLabel(nome == "" ? newRowHeader->text() : nome);

    if(chart->series().size() == 1)
        dynamic_cast<QPieSeries*>(chart->series()[0])->append(slice);
    else {
        QPieSeries* serie = new QPieSeries();
        serie->append(dynamic_cast<QPieSlice*>(slice));
        chart->addSeries(serie);
    }
}

void MainWidget::addIstoElement(QString nome) {
    QBarSet* set = new QBarSet(nome == "" ? newRowHeader->text() : nome);

    if(chart->series().size() == 1)
        dynamic_cast<QBarSeries*>(chart->series()[0])->append(set);
    else {
        QBarSeries* serie = new QBarSeries();
        serie->append(dynamic_cast<QBarSet*>(set));
        chart->addSeries(serie);
    }
    chart->createDefaultAxes();
}

void MainWidget::addCartElement(QString nome) {
    QLineSeries* serie = new QLineSeries();
    serie->setName(nome == "" ? newRowHeader->text() : nome);
    chart->addSeries(serie);
    chart->createDefaultAxes();
}

void MainWidget::addTableColumn(QString nome) {
    hTableHeader.push_back(nome == "" ? newColHeader->text().replace(',','.') : nome);
    table->setColumnCount(table->columnCount()+1);
    table->setHorizontalHeaderLabels(hTableHeader);
}

void MainWidget::addAreoValue(int row, double value) {
    QPieSeries* serie = dynamic_cast<QPieSeries*>(chart->series()[0]);
    QPieSlice* slice = serie->slices()[row];
    slice->setValue(value == -1 ? table->item(row,0)->text().toDouble() : value);
}

void MainWidget::addIstoValue(int row, int col, double value) {
    QBarSeries* serie = dynamic_cast<QBarSeries*>(chart->series()[0]);
    QBarSet* set = serie->barSets()[row];

    if(col == set->count()) //devo aggiungerlo alla fine perche nuovo
        set->append(value == -1 ? table->item(row,col)->text().toDouble() : value);
    else if(col < set->count()) //devo sostituire perche gia` inserito nel set
        set->replace(col, value == -1 ? table->item(row,col)->text().toDouble() : value);
    else
        removeTableCell(row,col);
}

void MainWidget::addCartValue(int row, int col, double value) {
    QLineSeries* serie = dynamic_cast<QLineSeries*>(chart->series()[row]);
    QPointF punto((hTableHeader[col].replace(',','.')).toDouble(), value == -1 ? table->item(row,col)->text().toDouble() : value);

    if(col == serie->count()) //devo aggiungerlo alla fine perche nuovo
        serie->append(punto);
    else if(col < serie->count()) //devo sostituire perche gia` inserito
        serie->replace(col, punto);
    else
        showWarning("Errore, valore non aggiunto.\nDefinire prima i valori precedenti.");
}

void MainWidget::addTableValue(int row, int col, QString value) {
    QTableWidgetItem *cella = new QTableWidgetItem;
    cella->setText(value);
    table->setItem(row, col, cella);
}

void MainWidget::removeTableColumn() {
    hTableHeader.removeAt(selectedColumn->value());
    table->removeColumn(selectedColumn->value());
}

void MainWidget::removeTableCell(int row, int col) {
    if(table->item(row,col)->text() != "-")
        showWarning("Errore, valore non aggiunto.\nDefinire prima i valori precedenti.");
    table->item(row,col)->setText("-");
}

void MainWidget::removeIstoValue() {
    QBarSeries* serie = dynamic_cast<QBarSeries*>(chart->series()[0]);

    for(auto set : serie->barSets())
        set->remove(selectedColumn->value());
}

void MainWidget::removeCartValue() {
    for(auto serie : chart->series()) {
        if(selectedColumn->value() <= dynamic_cast<QLineSeries*>(serie)->count()-1)
            dynamic_cast<QLineSeries*>(serie)->remove(selectedColumn->value());
    }
}

void MainWidget::removeTableRow() {
    vTableHeader.removeAt(selectedRow->value());
    table->removeRow(selectedRow->value());
}

void MainWidget::removeAreoElement() {
    QPieSeries* serie = dynamic_cast<QPieSeries*>(chart->series()[0]);
    serie->remove(serie->slices()[selectedRow->value()]);
}

void MainWidget::removeIstoElement() {
    QBarSeries* serie = dynamic_cast<QBarSeries*>(chart->series()[0]);
    serie->remove(serie->barSets()[selectedRow->value()]);
}

void MainWidget::removeCartElement() {
    chart->removeSeries(chart->series()[selectedRow->value()]);
}

void MainWidget::showWarning(QString s) {
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* label = new QLabel(s, dialog);
    label->setAlignment(Qt::AlignCenter);
    QPushButton* button = new QPushButton("OK", dialog);

    layout->addWidget(label);
    layout->addWidget(button);

    connect(button, SIGNAL(clicked(bool)), dialog, SLOT(close()));

    dialog->show();
}

void MainWidget::clearChart() {
    chart = new QChart();
    chart_view->setChart(chart);
    XAxLabel = new QLabel();
    YAxLabel = new QLabel();
}

void MainWidget::updateChart() {
    for(auto line : chart->series()) {
        chart->removeSeries(line);
        chart->addSeries(line);
        chart->createDefaultAxes();
    }
}

void MainWidget::updateIstoAxes() {
    QBarCategoryAxis *x_axis = new QBarCategoryAxis();
    x_axis->append(hTableHeader);
    chart->createDefaultAxes();
    chart->setAxisX(x_axis,chart->series()[0]);
    if(YAxLabel->text() != "") {
        chart->axisY()->setTitleText(YAxLabel->text());
    }
}

void MainWidget::updateCartAxes() {
    if(XAxLabel->text() != "") {
        chart->axisX()->setTitleText(XAxLabel->text());
    }
    if(YAxLabel->text() != "") {
        chart->axisY()->setTitleText(YAxLabel->text());
    }
}

QString MainWidget::getNewRowHeader() const {
    return newRowHeader->text();
}

QString MainWidget::getNewColHeader() const {
    return newColHeader->text();
}

int MainWidget::getTableRowsCount() const {
    return table->rowCount();
}

int MainWidget::getTableColsCount() const {
    return table->columnCount();
}

QString MainWidget::getChartTitle() const {
    return chart->title();
}

QString MainWidget::getXLabel() const {
    return chart->axisX()->titleText();
}

QString MainWidget::getYLabel() const {
    return chart->axisY()->titleText();
}

QString MainWidget::getTableVHeader(int row) const {
    return vTableHeader[row];
}

QString MainWidget::getTableHHeader(int col) const {
    return hTableHeader[col];
}

double MainWidget::getTableValue(int row, int col) const {
    return table->item(row,col) ? table->item(row,col)->data(0).toDouble() : 0;
}

int MainWidget::getSelectedColumn() const {
    return selectedColumn->value();
}

int MainWidget::getSelectedRow() const {
    return selectedRow->value();
}

QString MainWidget::getSavePosition(QString s) {
    QString path_for_file = QFileDialog::getSaveFileName(
                this, s, "/home", tr("XML doc (*.xml)"));
    if(path_for_file == "")
        throw std::runtime_error("Nessuna posizione selezionata.\nSalvataggio annullato.");

    return path_for_file;
}

QString MainWidget::getFile(QString s) {
    QString file_path = QFileDialog::getOpenFileUrl(
                this, s, QUrl("/home"), tr("XML doc (*.xml)")).path();
    if(file_path == "")
        throw std::runtime_error("Nessun file selezionato.\nCaricamento annullato.");

    return file_path;
}

//------SEGNALI------

void MainWidget::warningNew() {
    if(chart->title() != "") {
        QDialog* dialog = new QDialog;
        QVBoxLayout* layout = new QVBoxLayout(dialog);

        QLabel *msg = new QLabel("Attenzione,\nproseguendo tutto quello che non è stato\nsalvato andrà perso. Continuare?", dialog);
        msg->setAlignment(Qt::AlignCenter);
        QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

        layout->addWidget(msg);
        layout->addWidget(buttonbox);

        connect(buttonbox, SIGNAL(accepted()), this, SLOT(openNew()));
        connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

        connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

        dialog->show();
    }
    else
        openNew();
}

void MainWidget::openNew() {
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    areogramma = new QRadioButton("Areogramma", dialog);
    istogramma = new QRadioButton("Istogramma", dialog);
    cartesiano = new QRadioButton("Cartesiano", dialog);
    QHBoxLayout* ly_bottoni = new QHBoxLayout();
    ly_bottoni->addWidget(areogramma);
    ly_bottoni->addWidget(istogramma);
    ly_bottoni->addWidget(cartesiano);
    layout->addLayout(ly_bottoni);

    chart_title = new QLabel();
    QLabel* label = new QLabel("Titolo del grafico: ", dialog);
    QLineEdit* titolo = new QLineEdit(dialog);QHBoxLayout* ly_titolo = new QHBoxLayout();
    ly_titolo->addWidget(label);
    ly_titolo->addWidget(titolo);
    layout->addLayout(ly_titolo);

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
    layout->addWidget(buttonbox);

    connect(titolo, SIGNAL(textEdited(QString)), chart_title, SLOT(setText(QString)));

    connect(buttonbox, SIGNAL(accepted()), this, SLOT(setChart()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningNew()));
    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(clearView()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}

void MainWidget::setChart() {
    if(areogramma->isChecked())
        controller->setAreogramma();
    if(istogramma->isChecked())
        controller->setIstogramma();
    if(cartesiano->isChecked())
        controller->setCartesiano();

    clearChart();

    controller->setChartTitle();
}

void MainWidget::addRow() {
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QHBoxLayout* ly_nome = new QHBoxLayout();
    newRowHeader = new QLabel();
    QLabel* nome_riga = new QLabel("inserire il nome della riga: ", dialog);
    QLineEdit* ledit = new QLineEdit(dialog);
    ly_nome->addWidget(nome_riga);
    ly_nome->addWidget(ledit);

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

    layout->addLayout(ly_nome);
    layout->addWidget(buttonbox);

    connect(ledit, SIGNAL(textEdited(QString)), newRowHeader, SLOT(setText(QString)));

    connect(buttonbox, SIGNAL(accepted()), controller, SLOT(insertRow()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningNewRow()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}

void MainWidget::addColumn() {
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QHBoxLayout* ly_nome = new QHBoxLayout();
    newColHeader = new QLabel();

    if(chart->title() != "" && cartesiano->isChecked()) {
        QLabel* valore_colonna = new QLabel("inserire il valore della colonna: ", dialog);
        QDoubleSpinBox* value = new QDoubleSpinBox(dialog);
        ly_nome->addWidget(valore_colonna);
        ly_nome->addWidget(value);
        newColHeader->setText("0.00");
        connect(value, SIGNAL(valueChanged(QString)), newColHeader, SLOT(setText(QString)));
    }
    else {
        QLabel* nome_colonna = new QLabel("inserire il nome della colonna: ", dialog);
        QLineEdit* ledit = new QLineEdit(dialog);
        ly_nome->addWidget(nome_colonna);
        ly_nome->addWidget(ledit);
        connect(ledit, SIGNAL(textEdited(QString)), newColHeader, SLOT(setText(QString)));
    }

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

    layout->addLayout(ly_nome);
    layout->addWidget(buttonbox);

    connect(buttonbox, SIGNAL(accepted()), controller, SLOT(insertColumn()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningNewColumn()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}

void MainWidget::removeColumn() {
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QHBoxLayout* ly_value = new QHBoxLayout();
    QLabel* label = new QLabel("selezionare la colonna\nda eliminare: ", dialog);
    selectedColumn = new QSpinBox();
    selectedColumn->setMaximum(hTableHeader.size()-1);
    selectedColumn->setMinimum(0);
    ly_value->addWidget(label);
    ly_value->addWidget(selectedColumn);

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

    layout->addLayout(ly_value);
    layout->addWidget(buttonbox);

    connect(buttonbox, SIGNAL(accepted()), controller, SLOT(removeColumn()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningRemoveColumn()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}

void MainWidget::addXAxisLabel() {
    QDialog *dialog = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QHBoxLayout *edit_ly = new QHBoxLayout();
    XAxLabel = new QLabel();
    QLabel* label = new QLabel("inserire il nome per l'asse x", dialog);
    QLineEdit* ledit = new QLineEdit(dialog);
    edit_ly->addWidget(label);
    edit_ly->addWidget(ledit);

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

    layout->addLayout(edit_ly);
    layout->addWidget(buttonbox);

    connect(ledit, SIGNAL(textEdited(QString)), XAxLabel, SLOT(setText(QString)));

    connect(buttonbox, SIGNAL(accepted()), controller, SLOT(addXLabel()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningAx()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}

void MainWidget::addYAxisLabel() {
    QDialog *dialog = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QHBoxLayout *edit_ly = new QHBoxLayout();
    YAxLabel = new QLabel();
    QLabel* label = new QLabel("inserire il nome per l'asse y", dialog);
    QLineEdit* ledit = new QLineEdit(dialog);
    edit_ly->addWidget(label);
    edit_ly->addWidget(ledit);

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

    layout->addLayout(edit_ly);
    layout->addWidget(buttonbox);

    connect(ledit, SIGNAL(textEdited(QString)), YAxLabel, SLOT(setText(QString)));

    connect(buttonbox, SIGNAL(accepted()), controller, SLOT(addYLabel()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningAx()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}

void MainWidget::removeRow() {
    QDialog* dialog = new QDialog;
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QHBoxLayout* ly_value = new QHBoxLayout();
    QLabel* label = new QLabel("selezionare la riga\nda eliminare: ", dialog);
    selectedRow = new QSpinBox();
    selectedRow->setMaximum(vTableHeader.size()-1);
    selectedRow->setMinimum(0);
    ly_value->addWidget(label);
    ly_value->addWidget(selectedRow);

    QDialogButtonBox* buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);

    layout->addLayout(ly_value);
    layout->addWidget(buttonbox);

    connect(buttonbox, SIGNAL(accepted()), controller, SLOT(removeRow()));
    connect(buttonbox, SIGNAL(accepted()), dialog, SLOT(accept()));

    connect(buttonbox, SIGNAL(rejected()), controller, SLOT(warningRemoveRow()));
    connect(buttonbox, SIGNAL(rejected()), dialog, SLOT(reject()));

    dialog->show();
}
