
#include "BlobField.h"

BlobField::BlobField(string fieldName, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoFilled):
    Field(fieldName, BLOB, isPrimaryKey, isUnique, isNullable, isAutoFilled), _fieldValue(NULL) {}

void BlobField::setValue(istream &value) {
    setNull(false);
    _fieldValue = value;
}

istream BlobField::getValue() {
    return _fieldValue;
}

void BlobField::setParameter(int parameterNumber, DBConnection connection) {
    connection.setBlob(parameterNumber, getValue());
}

string BlobField::generateColumnSQL() {
    string fieldType = " BLOB";

    //Supposedly BLOB fields cannot have default values in MySQL.

    return getName() + fieldType;
}
