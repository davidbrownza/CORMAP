#include "Field.h"
#include <stdexcept>

using namespace std;

class CharField: public Field {
    
    private:
        string _fieldValue;
        unsigned int _maxLength;
        
    public:
        CharField(string name, int maxLength, string defaultValue="", bool primary=false, bool unique=false, bool nullable=true);
        
        void setValue(string value);
        string getValue();

        int getMaxLength();
        string checkMaxLength(string newValue);
};