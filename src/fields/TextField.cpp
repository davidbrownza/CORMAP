#include "TextField.h"

TextField::TextField(string fieldName, string defaultValue, bool primaryKey, bool unique, bool nullable): 
    Field(fieldName, TEXT, primaryKey, unique, nullable) { 
    _fieldValue = defaultValue;
} 

void TextField::setValue(string value) {
    setNull(false);
    _fieldValue = value;
}

string TextField::getValue() {
    return _fieldValue;
}
