#ifndef BOOLEANFIELD_H
#define BOOLEANFIELD_H

#include "Field.h"

using namespace std;

class BooleanField: public Field {
    
    private:
        bool _fieldValue;
        
    public:
        BooleanField(string fieldName, bool defaultValue=false, bool primaryKey=false, bool unique=false, bool nullable=true);
        
        void setValue(bool value);
        bool getValue();
};

#endif
