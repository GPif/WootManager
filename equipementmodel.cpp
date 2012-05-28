#include "equipementmodel.h"
#include <QDebug>

EquipementModel::EquipementModel(QObject *parent)
{
}

EquipementModel::EquipementModel(QList< QPair < float,ObjArsenal> > objectList, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->equip=objectList;
}

int EquipementModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return equip.size();
}

int EquipementModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
        return 5;
}

QVariant EquipementModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= equip.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
         ObjArsenal obj = (equip.at(index.row())).second;
         float quantity = (equip.at(index.row())).first;

        if (index.column() == 0)
            return quantity;
        else if (index.column() == 1)
            return obj.getId();
        else if (index.column() == 2)
            return obj.getName();
        else if (index.column() == 3)
            return obj.getEnc();
        else if (index.column() == 4)
            return obj.getValue();
    }
    return QVariant();
}

QVariant EquipementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Nb");
            case 1:
                return tr("Id");

            case 2:
                return tr("Nom");

            case 3:
                return tr("Encombrement");

            case 4:
                return tr("Prix");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool EquipementModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        ObjArsenal obj(-1,"",0,0);
        QPair<float,ObjArsenal> pair(0,obj);
        equip.insert(position, pair);
    }
    endInsertRows();
    return true;
}

bool EquipementModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        equip.removeAt(position);
    }
    endRemoveRows();
    return true;
}

bool EquipementModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
        if (index.isValid() && role == Qt::EditRole) {
                int row = index.row();

                ObjArsenal p = equip.value(row).second;
                float quantity = equip.value(row).first;

                if (index.column() == 0)
                        quantity=value.toFloat();
                else if (index.column() == 1)
                        p.setId(value.toInt());
                else if (index.column() == 2)
                        p.setName(value.toString());
                else if (index.column() == 3)
                        p.setEnc(value.toInt());
                else if (index.column() == 4)
                        p.setValue(value.toInt());
        else
            return false;

                QPair<float,ObjArsenal> pair(quantity,p);
        equip.replace(row, pair);
                emit(dataChanged(index, index));

        return true;
        }

        return false;
}

Qt::ItemFlags EquipementModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList < QPair < float,ObjArsenal> > EquipementModel::getList()
{
    return equip;
}

float EquipementModel::getTotalEnc(){
    int i;
    float totalenc=0;
    for (i=0;i<equip.size();++i){
        float q=equip.at(i).first;
        ObjArsenal obj=equip.at(i).second;
        totalenc += q*(obj.getEnc());
    }
    return totalenc;
}

float EquipementModel::getTotalValue(){
    int i;
    float totalcal=0;
    for (i=0;i<equip.size();++i){
        float q=equip.at(i).first;
        ObjArsenal obj=equip.at(i).second;
        totalcal += q*(obj.getValue());
    }
    return totalcal;
}

bool EquipementModel::alreadyHave(ObjArsenal obj){
    int id = obj.getId();
    int i;
    for(i=0;i<equip.size();i++){
        ObjArsenal obj = equip.at(i).second;
        int tmp = obj.getId();
        if (tmp == id) return true;
    }
    return false;
}

void EquipementModel::add_by_obj_Id(float q, int id){
    int i;
    for(i=0;i<equip.size();i++){
        QModelIndex ind = this->index(i,1);
        ObjArsenal obj = equip.at(i).second;
        int tmp = obj.getId();
        if (tmp == id){
            ind = this->index(i,0);
            int cur = this->data(ind,Qt::DisplayRole).toInt();
            int newq = cur+q;
            this->setData(ind,newq);
        }
    }
    return;
}
