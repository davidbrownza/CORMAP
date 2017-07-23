#include "Field.h"

using namespace std;

class FloatField: public Field {
    
    private:
        double fieldValue;
        
    public:
        FloatField(string name, double defaultValue=0, bool primary=false, bool unique=false, bool nullable=true);
        
        void setValue(double value);        
        double getValue();
};
