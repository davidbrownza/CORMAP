#include "FloatField.h"

FloatField::FloatField(string fieldName, double defaultValue, bool primaryKey, bool unique, bool nullable): 
    Field(fieldName, FLOAT, primaryKey, unique, nullable) { 
    _fieldValue = defaultValue;
} 

void FloatField::setValue(double value) {
    setNull(false);
    _fieldValue = value;
}

double FloatField::getValue() {
    return _fieldValue;
}
