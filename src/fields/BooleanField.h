#include "Field.h"

using namespace std;

class BooleanField: public Field {
    
    private:
        bool _fieldValue;
        
    public:
        BooleanField(string name, bool defaultValue=false, bool primary=false, bool unique=false, bool nullable=true);
        
        void setValue(bool value);
        bool getValue();
};
