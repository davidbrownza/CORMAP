#include "CharField.h"
#include <stdexcept>

CharField::CharField(string fieldName, int maxLength, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoFilled):
    Field(fieldName, CHAR, isPrimaryKey, isUnique, isNullable, isAutoFilled), _fieldValue(defaultValue), _defaultValue(defaultValue), _maxLength(maxLength) {}

void CharField::setValue(string value) {
    if (value.length() > _maxLength) {
        throw length_error("Field value exeeds the maximum allowed length");
    }

    setNull(false);
    _fieldValue = value;
}

string CharField::getValue() {
    return _fieldValue;
}

int CharField::getMaxLength() {
    return _maxLength;
}

void CharField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setString(parameterNumber, getValue());
}

string CharField::generateColumnSQL() {
    string fieldType = " VARCHAR(" + to_string(_maxLength) + ")";

    string defaultValue = "";
    if (isAutoFilled() == true) {
         defaultValue = " DEFAULT '" + _defaultValue + "'";
    }

    return getName() + fieldType + defaultValue;
}
