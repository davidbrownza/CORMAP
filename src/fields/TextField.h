#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Field.h"

using namespace std;

class TextField: public Field {

    private:
        string _fieldValue;
        string _defaultValue;

    public:
        TextField(string fieldName, string defaultValue="", bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true, bool isAutoFilled=false);

        void setValue(string value);
        string getValue();

        void setParameter(int parameterNumber, DBConnection connection);
        string generateColumnSQL();
};

#endif
