#include "Field.h"

Field::Field(string &fieldName, FieldType fieldType, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoFilled) :
    _fieldName(fieldName), _fieldType(fieldType), _isPrimaryKey(isPrimaryKey), _isUnique(isUnique), _isNullable(isNullable), _isAutoFilled(isAutoFilled) {
        _isNull = true;
    }

string Field::getName() {
    return _fieldName;
}

FieldType Field::getType() {
    return _fieldType;
}

bool Field::isUnique() {
    return _isUnique;
}

bool Field::isPrimaryKey() {
    return _isPrimaryKey;
}

bool Field::isAutoFilled() {
    return _isAutoFilled;
}

bool Field::isNullable() {
    return _isNullable;
}

bool Field::isNull() {
    return _isNull;
}

void Field::setNull(bool isNull) {
    _isNull = isNull;
}
