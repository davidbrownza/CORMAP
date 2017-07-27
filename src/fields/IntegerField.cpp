#include "IntegerField.h"

IntegerField::IntegerField(string fieldName, int defaultValue, bool primaryKey, bool unique, bool nullable, bool autoIncrement): 
    Field(fieldName, INTEGER, primaryKey, unique, nullable, autoIncrement) { 
    _fieldValue = defaultValue;
    _autoIncrement = autoIncrement; //Should this be passed to Field (above)?
}

void IntegerField::setValue(int value) {
    setNull(false);
    _fieldValue = value;
}

int IntegerField::getValue() {
    return _fieldValue;
}
