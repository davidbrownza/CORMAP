#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "Field.h"

using namespace std;

class TextField: public Field {
    
    private:
        string fieldValue;
        
    public:
        TextField(string name, string defaultValue="", bool primary=false, bool unique=false, bool nullable=true);
        
        void setValue(string value);        
        string getValue();
};

#endif
