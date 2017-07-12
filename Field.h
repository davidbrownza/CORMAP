#include <string>
#include <iostream>
#include <exception>

using namespace std;

enum FieldType { INTEGER, FLOAT, TEXT, CHAR };

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
        Field(string name, FieldType type, bool primary=false, bool unique=false, bool null=true, bool autoF=false) {
            fieldName = name;
            fieldType = type;
            primaryKey = primaryKey;
            uniqueValue = unique;
            nullable = null;
            autoFilled = autoF;
        }
        
        string getName() {
            return fieldName;
        }
        
        FieldType getType() {
            return fieldType;
        }
        
        bool isUnique() {
            return uniqueValue;
        }
        
        bool isPrimaryKey() {
            return primaryKey;
        }
        
        bool isAutoFilled() {
            return autoFilled;
        }
        
        bool isNullable() {
            return nullable;
        }
        
        bool isNull() {
            return _isNull;
        }
        
        void setNull(bool null) {
            _isNull = null;
        }
};

class IntegerField: public Field {
    
    private:
        int fieldValue;
        bool autoIncrement;
	    
    public:
        IntegerField(string name, int defaultValue=0, bool primary=false, bool unique=false, bool nullable=true, bool autoInc=false): 
            Field(name, INTEGER, primary, unique, nullable, autoInc) 
        { 
            fieldValue = defaultValue;
            autoIncrement = autoInc;
        }
        
        void setValue(int value) {
            setNull(false);
            fieldValue = value;
        }
        
        int getValue() {
            return fieldValue;
        }
};

class FloatField: public Field {
    
    private:
        double fieldValue;
	    
    public:
        FloatField(string name, double defaultValue=0, bool primary=false, bool unique=false, bool nullable=true): 
            Field(name, FLOAT, primary, unique, nullable) 
        { 
            fieldValue = defaultValue;
        } 
        
        void setValue(double value) {
            setNull(false);
            fieldValue = value;
        }
        
        double getValue() {
            return fieldValue;
        }
};

class TextField: public Field {
    
    private:
        string fieldValue;
	    
    public:
        TextField(string name, string defaultValue="", bool primary=false, bool unique=false, bool nullable=true): 
            Field(name, TEXT, primary, unique, nullable) 
        { 
            fieldValue = defaultValue;
        } 
        
        void setValue(string value) {
            setNull(false);
            fieldValue = value;
        }
        
        string getValue() {
            return fieldValue;
        }
};

class CharField: public Field {
    
    private:
        string _fieldValue;
        int _maxLength;
        
    public:
        CharField(string name, int maxLength, string defaultValue="", bool primary=false, bool unique=false, bool nullable=true):
            Field(name, CHAR, primary, unique, nullable) 
        { 
            _fieldValue = defaultValue;
            _maxLength = maxLength;
        } 
        
        void setValue(string value) {
            setNull(false);
            _fieldValue = checkMaxLength(value);
        }
        
        string getValue() {
            return _fieldValue;
        }
        
        int getMaxLength() {
            return _maxLength;
        }
        
        string checkMaxLength(string newValue) {
            if (newValue.length() > _maxLength) {
                throw length_error("Field value exeeds Max Length");
            }
            return newValue;            
        }
};
