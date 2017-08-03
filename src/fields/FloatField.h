#ifndef FLOATFIELD_H
#define FLOATFIELD_H

#include "Field.h"

using namespace std;

class FloatField: public Field {

    private:
        double _fieldValue;
        double _defaultValue;

    public:
        FloatField(string fieldName, double defaultValue=0, bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true);

        void setValue(double value);
        double getValue();

        void setParameter(int parameterNumber, DBConnection connection);
        string generateTableSQL();
};

#endif
