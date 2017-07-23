#ifndef FIELD_H
#define FIELD_H

#include <string>

using namespace std;

enum FieldType { INTEGER, FLOAT, TEXT, CHAR, BOOLEAN };

class Field {
    
    private:
        string fieldName;
        FieldType fieldType;
        bool primaryKey;
        bool uniqueValue;
        bool nullable;
        bool _isNull;
        bool autoFilled;
    
    public:
        Field(string name, FieldType type, bool primary=false, bool unique=false, bool null=true, bool autoF=false);
        
        string getName();        
        FieldType getType();        
        bool isUnique();        
        bool isPrimaryKey();        
        bool isAutoFilled();        
        bool isNullable();        
        bool isNull();        
        void setNull(bool null);
};

#endif
