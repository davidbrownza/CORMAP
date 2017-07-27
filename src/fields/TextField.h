#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Field.h"

using namespace std;

class TextField: public Field {
    
    private:
        string _fieldValue;
        
    public:
        TextField(string fieldName, string defaultValue="", bool primaryKey=false, bool unique=false, bool nullable=true);
        
        void setValue(string value);        
        string getValue();
};

#endif
