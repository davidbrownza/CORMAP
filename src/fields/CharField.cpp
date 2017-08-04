#include "CharField.h"
#include <stdexcept>

CharField::CharField(string fieldName, int maxLength, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable):
    Field(fieldName, CHAR, isPrimaryKey, isUnique, isNullable), _fieldValue(defaultValue), _maxLength(maxLength) {}

void CharField::setValue(string value) {
    setNull(false);
    _fieldValue = checkMaxLength(value);
}

string CharField::getValue() {
    return _fieldValue;
}

int CharField::getMaxLength() {
    return _maxLength;
}

// TODO: should be a void method or truncate the value
string CharField::checkMaxLength(string newValue) {
    if (newValue.length() > _maxLength) {
        throw length_error("Field value exeeds the maximum allowed length");
    }
    return newValue;
}

void CharField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setString(parameterNumber, getValue());
}
