#ifndef MONEYDELEGATE_H
#define MONEYDELEGATE_H
#include <QStyledItemDelegate>

class moneyDelegate
{
        Q_OBJECT

public:
    moneyDelegate(QWidget *parent = 0): QStyledItemDelegate(parent) {}
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;
         QSize sizeHint(const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
         QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;
         void setEditorData(QWidget *editor, const QModelIndex &index) const;
         void setModelData(QWidget *editor, QAbstractItemModel *model,
                           const QModelIndex &index) const;

private:
         QString toCo(float q);


#endif // MONEYDELEGATE_H
