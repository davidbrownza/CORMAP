#ifndef BOOLEANFIELD_H
#define BOOLEANFIELD_H

#include "Field.h"

using namespace std;

class BooleanField: public Field {

    private:
        bool _fieldValue;

    public:
        BooleanField(string fieldName, bool defaultValue=false, bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true);

        void setValue(bool value);
        bool getValue();

        void setParameter(int parameterNumber, DBConnection connection);
};

#endif
