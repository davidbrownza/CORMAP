#include "IntegerField.h"

IntegerField::IntegerField(string name, int defaultValue, bool primary, bool unique, bool nullable, bool autoInc): 
    Field(name, INTEGER, primary, unique, nullable, autoInc) { 
    fieldValue = defaultValue;
    autoIncrement = autoInc;
}

void IntegerField::setValue(int value) {
    setNull(false);
    fieldValue = value;
}

int IntegerField::getValue() {
    return fieldValue;
}
