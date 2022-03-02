#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QMenuBar>
#include <QtCharts>
#include <QChartView>
#include <QTableWidget>
#include <QStringList>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>


class Controller;

class MainWidget : public QWidget {
    Q_OBJECT
private:
    Controller* controller;

    QChart* chart;
    QChartView* chart_view;
    QMenu *file, *opzioni;
    QMenuBar* menuBar;
    QLabel *chart_title, *XAxLabel, *YAxLabel;

    QTableWidget* table;
    QStringList vTableHeader, hTableHeader;
    QLabel *newRowHeader, *newColHeader;

    QRadioButton *areogramma, *istogramma, *cartesiano;
    QSpinBox *selectedColumn, *selectedRow;
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void setController(Controller*);
    void setTitle(QString);
    void setXLabel(QString);
    void setYLabel(QString);
    void setAreoTable();

    void addMenu(QLayout*);
    void addTableRow(QString);
    void addAreoElement(QString);
    void addIstoElement(QString);
    void addCartElement(QString);
    void addTableColumn(QString);
    void addAreoValue(int,double);
    void addIstoValue(int,int,double);
    void addCartValue(int,int,double);
    void addTableValue(int,int,QString);

    void removeTableRow();
    void removeTableColumn();
    void removeTableCell(int,int);
    void removeIstoValue();
    void removeCartValue();
    void removeAreoElement();
    void removeIstoElement();
    void removeCartElement();

    void showWarning(QString);

    void clearChart();
    void updateChart();
    void updateIstoAxes();
    void updateCartAxes();

    QString getChartTitle() const;
    QString getXLabel() const;
    QString getYLabel() const;
    QString getNewRowHeader() const;
    QString getNewColHeader() const;
    int getTableRowsCount() const;
    int getTableColsCount() const;
    QString getTableVHeader(int) const;
    QString getTableHHeader(int) const;
    double getTableValue(int,int) const;
    int getSelectedColumn() const;
    int getSelectedRow() const;
    QString getSavePosition(QString);
    QString getFile(QString);

public slots:
    void warningNew();
    void openNew();
    void setChart();
    void clearTable();

    void addRow();
    void addColumn();
    void addXAxisLabel();
    void addYAxisLabel();

    void removeColumn();
    void removeRow();
};

#endif // MAINWIDGET_H
