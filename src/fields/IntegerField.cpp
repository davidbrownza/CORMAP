#include "IntegerField.h"

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

string IntegerField::generateTableSQL() {
    return getName() + " INTEGER DEFAULT " + to_string(_defaultValue);
}
