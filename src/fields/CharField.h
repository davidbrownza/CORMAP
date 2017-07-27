#ifndef CHARFIELD_H
#define CHARFIELD_H

#include "Field.h"
#include <stdexcept>

using namespace std;

class CharField: public Field {
    
    private:
        string _fieldValue;
        unsigned int _maxLength;
        
    public:
        CharField(string fieldName, int maxLength, string defaultValue="", bool primaryKey=false, bool unique=false, bool nullable=true);
        
        void setValue(string value);
        string getValue();

        int getMaxLength();
        string checkMaxLength(string newValue);
};

#endif
