#include "Field.h"

Field::Field(string fieldName, FieldType fieldType, bool primaryKey, bool unique, bool nullable, bool autoFilled) {
    _fieldName = fieldName;
    _fieldType = fieldType;
    _primaryKey = primaryKey;
    _unique = unique;
    _nullable = nullable;
    _autoFilled = autoFilled;
}

string Field::getName() {
    return _fieldName;
}

FieldType Field::getType() {
    return _fieldType;
}

bool Field::isUnique() {
    return _unique;
}

bool Field::isPrimaryKey() {
    return _primaryKey;
}

bool Field::isAutoFilled() {
    return _autoFilled;
}

bool Field::isNullable() {
    return _nullable;
}

bool Field::isNull() {
    return _isNull;
}

void Field::setNull(bool null) {
    _isNull = null;
}
