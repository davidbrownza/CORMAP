#ifndef INTEGERFIELD_H
#define INTEGERFIELD_H

#include "Field.h"

using namespace std;

class IntegerField: public Field {
    
    private:
        int _fieldValue;
        bool _autoIncrement;
        
    public:
        IntegerField(string fieldName, int defaultValue=0, bool primaryKey=false, bool unique=false, bool nullable=true, bool autoIncrement=false);
        
        void setValue(int value);        
        int getValue();
};

#endif
