#ifndef MODEL_H
#define MODEL_H

#include "DBConnection.h"
#include "Field.h"

#include <string>
#include <vector>

using namespace std;

enum Mode { UPDATE, IGNORE };


class Model
{
    private:
        void generateSQLParts(string &sqlHead, string &sqlBatch, string &sqlUpdate, Mode mode);
        string generateSQLTail(string sqlBatch, string sqlUpdate, int batchsize, Mode mode);
        
    public:
        Model(string name);
        ~Model();
        
        IntegerField* integerField(string name, int defaultValue=0, bool primary=false, bool unique=false, bool nullable=true, bool autoInc=false);
        FloatField* floatField(string name, double defaultValue=0, bool primary=false, bool unique=false, bool nullable=true);
        TextField* textField(string name, string defaultValue="", bool primary=false, bool unique=false, bool nullable=true);
         
        int insert(Mode mode=UPDATE);
        int insertBatch(vector<Model*> models, int batchsize=100, Mode mode=UPDATE);
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