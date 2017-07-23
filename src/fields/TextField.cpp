#include "TextField.h"

TextField::TextField(string name, string defaultValue, bool primary, bool unique, bool nullable): 
    Field(name, TEXT, primary, unique, nullable) { 
    fieldValue = defaultValue;
} 

void TextField::setValue(string value) {
    setNull(false);
    fieldValue = value;
}

string TextField::getValue() {
    return fieldValue;
}
