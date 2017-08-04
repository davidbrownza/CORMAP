#include "TextField.h"

TextField::TextField(string fieldName, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoFilled):
    Field(fieldName, TEXT, isPrimaryKey, isUnique, isNullable), _fieldValue(defaultValue), _defaultValue(defaultValue) {}

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

string TextField::generateColumnSQL() {
    string fieldType = " LONGTEXT";

    string defaultValue = "";
    if (isAutoFilled() == true) {
         defaultValue = " DEFAULT '" + _defaultValue + "'";
    }

    return getName() + fieldType + defaultValue;
}
