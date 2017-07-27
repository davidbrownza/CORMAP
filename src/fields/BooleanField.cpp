#include "BooleanField.h"

BooleanField::BooleanField(string fieldName, bool defaultValue, bool primaryKey, bool unique, bool nullable): 
    Field(fieldName, BOOLEAN, primaryKey, unique, nullable) { 
    _fieldValue = defaultValue;
} 

void BooleanField::setValue(bool value) {
    setNull(false);
    _fieldValue = value;
}

bool BooleanField::getValue() {
    return _fieldValue;
}
