#include "Field.h"

Field::Field(string name, FieldType type, bool primary, bool unique, bool null, bool autoF) {
    fieldName = name;
    fieldType = type;
    primaryKey = primaryKey;
    uniqueValue = unique;
    nullable = null;
    autoFilled = autoF;
}

string Field::getName() {
    return fieldName;
}

FieldType Field::getType() {
    return fieldType;
}

bool Field::isUnique() {
    return uniqueValue;
}

bool Field::isPrimaryKey() {
    return primaryKey;
}

bool Field::isAutoFilled() {
    return autoFilled;
}

bool Field::isNullable() {
    return nullable;
}

bool Field::isNull() {
    return _isNull;
}

void Field::setNull(bool null) {
    _isNull = null;
}
