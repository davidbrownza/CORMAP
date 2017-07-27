#include "Model.h"
#include <iostream>

Model::Model(string name) {
    tableName = name;
}

Model::~Model() {
    for (vector<Field*>::const_iterator it = fields.begin(); it != fields.end(); it++) {
        delete *it;
    } 
    fields.clear();
}

IntegerField* Model::integerField(string fieldName, int defaultValue, bool primaryKey, bool unique, bool nullable, bool autoIncrement) {
    IntegerField * f = new IntegerField(fieldName, defaultValue, primaryKey, unique, nullable, autoIncrement);
    fields.push_back(f);
    
    return f;
}

FloatField* Model::floatField(string fieldName, double defaultValue, bool primaryKey, bool unique, bool nullable) {
    FloatField * f = new FloatField(fieldName, defaultValue, primaryKey, unique, nullable);
    fields.push_back(f);
    
    return f;
}

TextField* Model::textField(string fieldName, string defaultValue, bool primaryKey, bool unique, bool nullable) {
    TextField * f = new TextField(fieldName, defaultValue, primaryKey, unique, nullable);
    fields.push_back(f);
    
    return f;
}

CharField* Model::charField(string fieldName, int maxLength, string defaultValue, bool primaryKey, bool unique, bool nullable) {
    CharField * f = new CharField(fieldName, maxLength, defaultValue, primaryKey, unique, nullable);
    fields.push_back(f);
    
    return f;
}

BooleanField* Model::booleanField(string fieldName, bool defaultValue, bool primaryKey, bool unique, bool nullable) {
    BooleanField * f = new BooleanField(fieldName, defaultValue, primaryKey, unique, nullable);
    fields.push_back(f);
    
    return f;
}

int Model::insert(Mode mode) {
    vector<Model*> models;
    models.push_back(this);
    
    return insertBatch(models, 1, mode);
}

int Model::insertBatch(vector<Model*> models, unsigned int batchsize, Mode mode) {
    unsigned int size = models.size();
    
    if (size < batchsize)
        batchsize = size;
        
    //workout the size of the last batch
    int rem = size % batchsize;
    unsigned int finalFullBatch = size - rem;    
    
    //generate SQL 
    string sqlHead; // INSERT INTO table_name (fields) VALUES
    string sqlBatch; // (?,?..,?)
    string sqlUpdate; // ON DUPLICATE KEY UPDATE field=VALUES(field),...
    generateSQLParts(sqlHead, sqlBatch, sqlUpdate, mode);
    
    string sqlTail = generateSQLTail(sqlBatch, sqlUpdate, batchsize, mode);
    
    //cout << sqlHead + sqlTail << endl;
    
    //prepare first statement
    conn.prepareStatement(sqlHead + sqlTail);
    
    int paramNum = 0;
    bool finalBatch = false;
    //iterate through the list of models inserting batches of the specified size
    for (unsigned int i = 0; i < models.size(); i++) {    
        Model * m = models[i];
        //iterate through the list of fields, adding them as parameters
        for (unsigned int j = 0; j < m->fields.size(); j++) {
            Field * f = m->fields[j];
            
            bool ignoreField = f->isAutoFilled();
        
            if (!ignoreField) {
                paramNum++;
                
                if (f->isNull()) {
                    conn.setNull(paramNum);
                    continue;
                }
                    
                switch(f->getType()) {

                    case INTEGER: {
                        IntegerField * i = static_cast <IntegerField*>(f);
                        conn.setInt(paramNum, i->getValue());
                        break;
                    }

                    case FLOAT: {
                        FloatField * i = static_cast <FloatField*>(f);
                        conn.setDouble(paramNum, i->getValue());
                        break;
                    }
                    
                    case TEXT: {
                        TextField * i = static_cast <TextField*>(f);
                        conn.setString(paramNum, i->getValue());
                        break;
                    }
                    
                    case CHAR: {
                        CharField * i = static_cast <CharField*>(f);
                        conn.setString(paramNum, i->getValue());
                        break;
                    }

                    case BOOLEAN: {
                        BooleanField * i = static_cast <BooleanField*>(f);
                        conn.setInt(paramNum, i->getValue());
                        break;
                    }
                }
            }
        }
                
        if (i+1 == size || (!finalBatch && (i+1) % batchsize == 0)) {        
            conn.executeStatement();
            
            //reset paramNum after execution
            paramNum = 0;
            
            //the final batch will require a prepared statement that is only as long as the remaining no. of models
            if (i+1 >= finalFullBatch) {
                finalBatch = true;
                
                sqlTail = generateSQLTail(sqlBatch, sqlUpdate, rem, mode);
                batchsize = rem;
            }
            
            conn.deleteStatement();         
            conn.prepareStatement(sqlHead + sqlTail);
        }        
    }  
    
    return 0;
}


int Model::truncate() {
    conn.prepareStatement("TRUNCATE " + tableName);
    conn.executeStatement();
    conn.deleteStatement();
    
    return 0;
}


int Model::setConnection(DBConnection connection) {    
    conn = connection;
    return 0;
}


DBConnection Model::getConnection() {
    return conn;
}


void Model::generateSQLParts(string &sqlHead, string &sqlBatch, string &sqlUpdate, Mode mode) {
    string sqlFields = "";
    sqlBatch = "(";
    sqlUpdate = " ON DUPLICATE KEY UPDATE ";
    
    bool firstField = true;
    
    for (unsigned int i = 0; i < fields.size(); i++) {
        Field* f = fields[i];
        
        bool ignoreField = f->isAutoFilled();
        
        if (!ignoreField) {
            if (firstField) {
                firstField = false;
                
                sqlFields +=  f->getName();
                sqlBatch += "?";
                
                if (mode == UPDATE) {
                    sqlUpdate += f->getName() + " = VALUES(" + f->getName() + ")";
                }
            } else {
                sqlFields +=  ", " + f->getName();
                sqlBatch += ",?";
                
                if (mode == UPDATE) {
                    sqlUpdate += ", " + f->getName() + " = VALUES(" + f->getName() + ")";
                }
            }
        }
    }
    
    sqlBatch += ")";
    
    if (mode == IGNORE) {
        sqlHead = "INSERT IGNORE INTO " + tableName + " (" +  sqlFields + ") VALUES ";
    } else {
        sqlHead = "INSERT INTO " + tableName + " (" +  sqlFields + ") VALUES ";
    }
}

string Model::generateSQLTail(string sqlBatch, string sqlUpdate, int batchsize, Mode mode) {
    string sqlTail = sqlBatch;
    
    for (int j = 1; j < batchsize; j++) {
        sqlTail += "," + sqlBatch;
    }
    
    if (mode == UPDATE) {
        sqlTail += sqlUpdate;
    }
    
    return sqlTail;
}
