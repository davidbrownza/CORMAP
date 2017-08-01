#ifndef INTEGERFIELD_H
#define INTEGERFIELD_H

#include "Field.h"

using namespace std;

class IntegerField: public Field {
    
    private:
        int _fieldValue;
        bool _isAutoIncremented;
        
    public:
        IntegerField(string fieldName, int defaultValue=0, bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true, bool isAutoIncremented=false);
        
        void setValue(int value);        
        int getValue();
        
        void setParameter(int parameterNumber, DBConnection connection);
};

#endif
