#include "IntegerField.h"
#include <string>

IntegerField::IntegerField(string fieldName, int defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoIncremented):
    Field(fieldName, INTEGER, isPrimaryKey, isUnique, isNullable, isAutoIncremented), _fieldValue(defaultValue), _defaultValue(defaultValue), _isAutoIncremented(isAutoIncremented) {}

void IntegerField::setValue(int value) {
    setNull(false);
    _fieldValue = value;
}

int IntegerField::getValue() {
    return _fieldValue;
}

void IntegerField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setInt(parameterNumber, getValue());
}

string IntegerField::generateColumnSQL() {
    string fieldType = " INTEGER";

    string defaultValue = "";
    if (isAutoFilled() == true) {
         defaultValue = " DEFAULT " + to_string(_defaultValue);
    }

    return getName() + fieldType + defaultValue;
}
