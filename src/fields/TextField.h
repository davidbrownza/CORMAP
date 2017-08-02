#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Field.h"

using namespace std;

class TextField: public Field {

    private:
        string _fieldValue;

    public:
        TextField(string fieldName, string defaultValue="", bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true);

        void setValue(string value);
        string getValue();

        void setParameter(int parameterNumber, DBConnection connection);
};

#endif
