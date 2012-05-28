#include "objarsenal.h"

ObjArsenal::ObjArsenal()
{
}

ObjArsenal::ObjArsenal(int id, QString name, int enc, int value){
    this->id=id;
    this->name=name;
    this->enc=enc;
    this->value = value;
}

int ObjArsenal::getId(){
    return this->id;
}

void ObjArsenal::setId(int id){
    this->id=id;
}

QString ObjArsenal::getName(){
    return name;
}

void ObjArsenal::setName(QString name){
    this->name = name;
}

int ObjArsenal::getEnc(){
    return enc;
}

void ObjArsenal::setEnc(int enc){
    this->enc = enc;
}

int ObjArsenal::getValue(){
    return this->value;
}

void ObjArsenal::setValue(int val){
    this->value=val;
}
