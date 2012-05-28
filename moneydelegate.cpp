#include "moneydelegate.h"

void moneyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (index.row() == 4) {
        painter->fillRect(option.rect, option.palette.highlight());

        starRating.paint(painter, option.rect, option.palette,
                         StarRating::ReadOnly);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize moneyDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.data().canConvert<StarRating>()) {
        StarRating starRating = qvariant_cast<StarRating>(index.data());
        return starRating.sizeHint();
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

QString moneyDelegate::toCo(float q){
    QString str;
    int co = (int) q/240;
    int pa = (int) (q-co*20)/12;
    float s = q-co*240-pa*12;
    str.sprintf("%d co %d pa %d s",co,pa,s);
    return str;
}
