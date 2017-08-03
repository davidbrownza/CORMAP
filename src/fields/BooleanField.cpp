
#include "BooleanField.h"

BooleanField::BooleanField(string fieldName, bool defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable):
    Field(fieldName, BOOLEAN, isPrimaryKey, isUnique, isNullable), _fieldValue(defaultValue), _defaultValue(defaultValue) {}

void BooleanField::setValue(bool value) {
    setNull(false);
    _fieldValue = value;
}

bool BooleanField::getValue() {
    return _fieldValue;
}

void BooleanField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setInt(parameterNumber, getValue());
}

string BooleanField::generateColumnSQL() {
    string fieldType = " TINYINT(1)";
    string defaultValue = _defaultValue == true ? " DEFAULT 1" : " DEFAULT 0";
    return getName() + fieldType + defaultValue;
}
