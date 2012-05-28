#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spinboxdelegate.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupModel();
    equipement = new EquipementModel();
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(4);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->resizeSection(1,300);

    ui->tableView_2->setModel(equipement);
    ui->tableView_2->hideColumn(1);
    ui->tableView_2->hideColumn(4);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->horizontalHeader()->resizeSection(2,300);

    ui->doubleSpinBox->setValue(1.00);

    connect(ui->searchLine, SIGNAL(textChanged(QString)), this, SLOT(setModelFilter(QString)));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(catchandadd()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(rmRow()));
    connect(this,SIGNAL(updateAll()),this,SLOT(updTot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add2equipement(float quantity,ObjArsenal obj){
    if(equipement->alreadyHave(obj)){
        int obj_id=obj.getId();
        equipement->add_by_obj_Id(quantity,obj_id);
    }else{
        equipement->insertRow(0);
        QModelIndex index;
        index = equipement->index(0,0);
        equipement->setData(index,quantity);
        index = equipement->index(0,1);
        equipement->setData(index,obj.getId());
        index = equipement->index(0,2);
        equipement->setData(index,obj.getName());
        index = equipement->index(0,3);
        equipement->setData(index,obj.getEnc());
        index = equipement->index(0,4);
        equipement->setData(index,obj.getValue());
    }
}

void MainWindow::setupModel(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("./armory.sqlite");
     if (!db.open()) {
         QString errtxt = (db.lastError()).text();
         QMessageBox::critical(0,"Unable to init db", errtxt, QMessageBox::Cancel);
         return;
     }

     model = new QSqlTableModel(this);
     model->setTable("objects");
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->select();
}

void MainWindow::setModelFilter(QString str){
    model->setFilter("name LIKE '%"+str+"%' ");
}

void MainWindow::catchandadd(){
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedIndexes();
    QList<int> pkeyList;
    foreach (QModelIndex index, indexList) {
        int curKey = index.row();
        if (! pkeyList.contains(curKey)){
            pkeyList << curKey;
        }
    }

    foreach (int tmp, pkeyList){
        QModelIndex ind;
        ObjArsenal * obj = new ObjArsenal();
        ind = model->index(tmp,0);
        obj->setId(model->data(ind).toInt());
        ind = model->index(tmp,1);
        obj->setName(model->data(ind).toString());
        ind = model->index(tmp,2);
        obj->setEnc(model->data(ind).toInt());
        ind = model->index(tmp,4);
        obj->setValue(model->data(ind).toInt());
        add2equipement(ui->doubleSpinBox->value(), * obj);
    }
    emit updateAll();
}

void MainWindow::rmRow(){
    QModelIndexList indexList = ui->tableView_2->selectionModel()->selectedIndexes();
    QList<int> pkeyList;
    foreach (QModelIndex index, indexList) {
        qDebug()<< "(" << index.row() << ";" << index.column() << ")";
        //equipement->removeRows(index.row(),1,index);
        if (! pkeyList.contains(index.row())){
            pkeyList.prepend(index.row());
        }
    }
    qDebug() << pkeyList;
    foreach (int tmp, pkeyList){
        qDebug() << tmp;
        equipement->removeRows(tmp,1);
    }

    emit updateAll();
}

void MainWindow::updTot(){
    float tot = equipement->getTotalEnc();
    QString str;
    //str.setNum(tot,'f');
    str.sprintf("%.2f",tot);
    ui->totalenc->setText(str);

    float tot2 = equipement->getTotalValue();
    QString str2;
    //str.setNum(tot,'f');
    str2 = toCo(tot2);
    ui->totalval->setText(str2);
}

QString MainWindow::toCo(float q){
    QString str;
    int co = (int) q/240;
    int pa = (int) (q-co*240)/12;
    float s = q-co*240-pa*12;
    str.sprintf("%d co %d pa %2.0f s",co,pa,s);
    return str;
}
