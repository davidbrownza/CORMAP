#include "Model.h"
#include <iostream>

Model::Model(string name) {
    tableName = name;
}

Model::~Model() {
    for(vector<Field*>::const_iterator it = fields.begin(); it != fields.end(); it++)
    {
        delete *it;
    } 
    fields.clear();
}

IntegerField* Model::integerField(string name, int defaultValue, bool primary, bool unique, bool nullable, bool autoInc)
{
    IntegerField * f = new IntegerField(name, defaultValue, primary, unique, nullable, autoInc);
    fields.push_back(f);
    
    return f;
}

FloatField* Model::floatField(string name, double defaultValue, bool primary, bool unique, bool nullable)
{
    FloatField * f = new FloatField(name, defaultValue, primary, unique, nullable);
    fields.push_back(f);
    
    return f;
}

TextField* Model::textField(string name, string defaultValue, bool primary, bool unique, bool nullable)
{
    TextField * f = new TextField(name, defaultValue, primary, unique, nullable);
    fields.push_back(f);
    
    return f;
}

CharField* Model::charField(string name, int maxLen, string defaultValue, bool primary, bool unique, bool nullable)
{
    CharField * f = new CharField(name, maxLen, defaultValue, primary, unique, nullable);
    fields.push_back(f);
    
    return f;
}

int Model::insert(Mode mode)
{
    vector<Model*> models;
    models.push_back(this);
    
    return insertBatch(models, 1, mode);
}

int Model::insertBatch(vector<Model*> models, int batchsize, Mode mode)
{
    int size = models.size();
	
	if(size < batchsize)
		batchsize = size;
    	
	//workout the size of the last batch
	int rem = size % batchsize;
	int finalFullBatch = size - rem;	
	
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
	for (int i = 0; i < models.size(); i++)
    {	
        Model * m = models[i];
        //iterate through the list of fields, adding them as parameters
        for (int j = 0; j < m->fields.size(); j++) {
            Field * f = m->fields[j];
            
            bool ignoreField = f->isAutoFilled();
        
            if (!ignoreField) {
                paramNum++;
                
                if (f->getType() == INTEGER)
                {
                    IntegerField * i = static_cast <IntegerField*>(f);
                    if (i->isNull()) {
                        conn.setNull(paramNum);
                    } else {
                        conn.setInt(paramNum, i->getValue());
                    }
                }
                else if(f->getType() == FLOAT)
                {
                    
                    FloatField * i = static_cast <FloatField*>(f);
                    if (i->isNull()) {
                        conn.setNull(paramNum);
                    } else {
                        conn.setDouble(paramNum, i->getValue());
                    }
                }
                else if(f->getType() == TEXT)
                {
                    TextField * i = static_cast <TextField*>(f);
                    if (i->isNull()) {
                        conn.setNull(paramNum);
                    } else {
                        conn.setString(paramNum, i->getValue());
                    }
                }
                else if(f->getType() == CHAR)
                {
                    CharField * i = static_cast <CharField*>(f);
                    if (i->isNull()) {
                        conn.setNull(paramNum);
                    } else {
                        conn.setString(paramNum, i->getValue());
                    }
                }
            }
        }
        	    
        if(i+1 == size || !finalBatch && (i+1) % batchsize == 0)
        {    	
            conn.executeStatement();
            
            //reset paramNum after execution
            paramNum = 0;
            
            //the final batch will require a prepared statement that is only as long as the remaining no. of models
            if(i+1 >= finalFullBatch)
            {
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


int Model::setConnection(DBConnection connection)
{	
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
    
	for (int i = 0; i < fields.size(); i++)
    {
        Field* f = fields[i];
        
        bool ignoreField = f->isAutoFilled();
        
        if (!ignoreField) {
            if (firstField)
            {
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
	
	for(int j = 1; j < batchsize; j++)
	{
		sqlTail += "," + sqlBatch;
	}
	
	if (mode == UPDATE) {
	    sqlTail += sqlUpdate;
	}
	
    return sqlTail;
}