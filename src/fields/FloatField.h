#ifndef FLOATFIELD_H
#define FLOATFIELD_H

#include "Field.h"

using namespace std;

class FloatField: public Field {
    
    private:
        double _fieldValue;
        
    public:
        FloatField(string fieldName, double defaultValue=0, bool primaryKey=false, bool unique=false, bool nullable=true);
        
        void setValue(double value);        
        double getValue();
};

#endif
