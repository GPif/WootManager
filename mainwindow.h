#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "equipementmodel.h"

#include <QMainWindow>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void add2equipement(float quantity,ObjArsenal obj);

public slots:
    void setModelFilter(QString str);
    void catchandadd();
    void updTot();
    void rmRow();

signals:
    void updateAll();

private:

    QString toCo(float q);
    QSqlTableModel *model;
    EquipementModel* equipement;

    Ui::MainWindow *ui;
    void setupModel();
};

#endif // MAINWINDOW_H
