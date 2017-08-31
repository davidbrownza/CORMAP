#ifndef BLOBFIELD_H
#define BLOBFIELD_H

#include "Field.h"

using namespace std;

class BlobField: public Field {

    private:
        istream _fieldValue;

    public:
        BlobField(string fieldName, bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true, bool isAutoFilled=true);

        void setValue(istream &value);
        istream getValue();

        void setParameter(int parameterNumber, DBConnection connection);
        string generateColumnSQL();
};

#endif
