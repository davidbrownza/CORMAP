#include "FloatField.h"

FloatField::FloatField(string fieldName, double defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable):
    Field(fieldName, FLOAT, isPrimaryKey, isUnique, isNullable) {
    _fieldValue = defaultValue;
}

void FloatField::setValue(double value) {
    setNull(false);
    _fieldValue = value;
}

double FloatField::getValue() {
    return _fieldValue;
}

void FloatField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setDouble(parameterNumber, getValue());
}
