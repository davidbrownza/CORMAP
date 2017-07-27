#ifndef MODEL_H
#define MODEL_H

#include "../conn/DBConnection.h"

#include "../fields/IntegerField.h"
#include "../fields/FloatField.h"
#include "../fields/TextField.h"
#include "../fields/CharField.h"
#include "../fields/BooleanField.h"

#include <string>
#include <vector>

using namespace std;

enum Mode { 
    UPDATE, IGNORE 
};

class Model {
    
    private:
        void generateSQLParts(string &sqlHead, string &sqlBatch, string &sqlUpdate, Mode mode);
        string generateSQLTail(string sqlBatch, string sqlUpdate, int batchsize, Mode mode);
        
    public:
        Model(string name);
        ~Model();
        
        IntegerField* integerField(string fieldName, int defaultValue=0, bool primaryKey=false, bool unique=false, bool nullable=true, bool autoIncrement=false);
        FloatField* floatField(string fieldName, double defaultValue=0, bool primaryKey=false, bool unique=false, bool nullable=true);
        TextField* textField(string fieldName, string defaultValue="", bool primaryKey=false, bool unique=false, bool nullable=true);
        CharField* charField(string fieldName, int maxLength, string defaultValue="", bool primaryKey=false, bool unique=false, bool nullable=true);
        BooleanField* booleanField(string fieldName, bool defaultValue=false, bool primaryKey=false, bool unique=false, bool nullable=true);
         
        int insert(Mode mode=UPDATE);
        int insertBatch(vector<Model*> models, unsigned int batchsize=100, Mode mode=UPDATE);
        int truncate();
        
        template<typename T> Model* getByID(T pk_value);
        
        int setConnection(DBConnection connection);
        DBConnection getConnection();
        
        string tableName;
        vector<Field*> fields;
        
    protected:
        
        DBConnection conn;
};

#endif
