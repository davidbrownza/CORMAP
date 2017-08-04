#ifndef CHARFIELD_H
#define CHARFIELD_H

#include "Field.h"
#include <stdexcept>

using namespace std;

class CharField: public Field {

    private:
        string _fieldValue;
        string _defaultValue;
        unsigned int _maxLength;

    public:
        CharField(string fieldName, int maxLength, string defaultValue="", bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true, bool isAutoFilled=false);

        void setValue(string value);
        string getValue();

        int getMaxLength();

        void setParameter(int parameterNumber, DBConnection connection);
        string generateColumnSQL();
};

#endif
