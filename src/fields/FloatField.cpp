#include "FloatField.h"

FloatField::FloatField(string name, double defaultValue, bool primary, bool unique, bool nullable): 
    Field(name, FLOAT, primary, unique, nullable) { 
    fieldValue = defaultValue;
} 

void FloatField::setValue(double value) {
    setNull(false);
    fieldValue = value;
}

double FloatField::getValue() {
    return fieldValue;
}
