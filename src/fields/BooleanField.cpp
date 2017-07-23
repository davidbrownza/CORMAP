#include "BooleanField.h"

BooleanField::BooleanField(string name, bool defaultValue, bool primary, bool unique, bool nullable): 
    Field(name, BOOLEAN, primary, unique, nullable) { 
    _fieldValue = defaultValue;
} 

void BooleanField::setValue(bool value) {
    setNull(false);
    _fieldValue = value;
}

bool BooleanField::getValue() {
    return _fieldValue;
}
