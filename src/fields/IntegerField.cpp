#include "IntegerField.h"

IntegerField::IntegerField(string fieldName, int defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool autoIncrement): 
    Field(fieldName, INTEGER, isPrimaryKey, isUnique, isNullable, autoIncrement) { 
    _fieldValue = defaultValue;
    _autoIncrement = autoIncrement;
}

void IntegerField::setValue(int value) {
    setNull(false);
    _fieldValue = value;
}

int IntegerField::getValue() {
    return _fieldValue;
}
