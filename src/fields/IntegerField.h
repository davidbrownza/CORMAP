#ifndef INTEGERFIELD_H
#define INTEGERFIELD_H

#include "Field.h"

using namespace std;

class IntegerField: public Field {
    
    private:
        int fieldValue;
        bool autoIncrement;
        
    public:
        IntegerField(string name, int defaultValue=0, bool primary=false, bool unique=false, bool nullable=true, bool autoInc=false);
        
        void setValue(int value);        
        int getValue();
};

#endif
