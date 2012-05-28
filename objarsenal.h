#ifndef OBJARSENAL_H
#define OBJARSENAL_H

#include <QString>

class ObjArsenal
{
public:
    ObjArsenal();
    ObjArsenal(int id, QString name, int enc, int value);

    int getId();
    void setId(int);
    QString getName();
    void setName(QString);
    int getEnc();
    void setEnc(int);
    int getValue();
    void setValue(int);

private:
    int id;
    QString name;
    int enc;
    int value;
};

#endif // OBJARSENAL_H
