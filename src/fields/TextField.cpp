#include "TextField.h"

TextField::TextField(string &fieldName, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable):
    Field(fieldName, TEXT, isPrimaryKey, isUnique, isNullable), _fieldValue(defaultValue) {}

void TextField::setValue(string value) {
    setNull(false);
    _fieldValue = value;
}

string TextField::getValue() {
    return _fieldValue;
}

void TextField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setString(parameterNumber, getValue());
}
