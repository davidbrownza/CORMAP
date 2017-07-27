#include "CharField.h"
#include <stdexcept>

CharField::CharField(string fieldName, int maxLength, string defaultValue, bool primaryKey, bool unique, bool nullable):
    Field(fieldName, CHAR, primaryKey, unique, nullable) { 
    _fieldValue = defaultValue;
    _maxLength = maxLength;
} 

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
