#include "IntegerField.h"

IntegerField::IntegerField(string fieldName, int defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoIncremented): 
    Field(fieldName, INTEGER, isPrimaryKey, isUnique, isNullable, isAutoIncremented) { 
    _fieldValue = defaultValue;
    _isAutoIncremented = isAutoIncremented;
}

void IntegerField::setValue(int value) {
    setNull(false);
    _fieldValue = value;
}

int IntegerField::getValue() {
    return _fieldValue;
}
