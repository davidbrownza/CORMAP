#ifndef FIELD_H
#define FIELD_H

#include <string>

using namespace std;

enum FieldType { 
    INTEGER, FLOAT, TEXT, CHAR, BOOLEAN 
};

class Field {
    
    private:
        string _fieldName;
        FieldType _fieldType;
        bool _isPrimaryKey;
        bool _isUnique;
        bool _isNullable;
        bool _isNull;
        bool _autoFilled;
    
    public:
        Field(string fieldName, FieldType fieldType, bool isPrimaryKey=false, bool isUnique=false, bool isNullable=true, bool autoFilled=false);
        
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
