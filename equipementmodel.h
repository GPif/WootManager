#ifndef EQUIPEMENTMODEL_H
#define EQUIPEMENTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "objarsenal.h"

class EquipementModel : public QAbstractTableModel
{
public:
    EquipementModel(QObject *parent=0);
    EquipementModel(QList< QPair < float,ObjArsenal> > objectList, QObject *parent=0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    QList< QPair < float,ObjArsenal> > getList();
    bool alreadyHave(ObjArsenal obj);
    void add_by_obj_Id(float q, int id);
    float getTotalEnc();
    float getTotalValue();

private:
    QList< QPair < float,ObjArsenal> > equip;
};

#endif // EQUIPEMENTMODEL_H
