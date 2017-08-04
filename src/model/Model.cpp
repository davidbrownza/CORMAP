#include "Model.h"
#include <iostream>

Model::Model(string name):
    tableName(name) {}

Model::~Model() {
    for (vector<Field*>::const_iterator it = fields.begin(); it != fields.end(); ++it) {
        delete *it;
    }
    fields.clear();
}

IntegerField* Model::integerField(string fieldName, int defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable, bool isAutoIncremented) {
    IntegerField * f = new IntegerField(fieldName, defaultValue, isPrimaryKey, isUnique, isNullable, isAutoIncremented);
    fields.push_back(f);

    return f;
}

FloatField* Model::floatField(string fieldName, double defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable) {
    FloatField * f = new FloatField(fieldName, defaultValue, isPrimaryKey, isUnique, isNullable);
    fields.push_back(f);

    return f;
}

TextField* Model::textField(string fieldName, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable) {
    TextField * f = new TextField(fieldName, defaultValue, isPrimaryKey, isUnique, isNullable);
    fields.push_back(f);

    return f;
}

CharField* Model::charField(string fieldName, int maxLength, string defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable) {
    CharField * f = new CharField(fieldName, maxLength, defaultValue, isPrimaryKey, isUnique, isNullable);
    fields.push_back(f);

    return f;
}

BooleanField* Model::booleanField(string fieldName, bool defaultValue, bool isPrimaryKey, bool isUnique, bool isNullable) {
    BooleanField * f = new BooleanField(fieldName, defaultValue, isPrimaryKey, isUnique, isNullable);
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

    if (size < batchsize) {
        batchsize = size;
    }

    //workout the size of the last batch
    int finalBatchSize = size % batchsize;
    unsigned int finalBatchStartIndex = size - finalBatchSize;

    string sqlHead, sqlBatch, sqlUpdate, sqlTail;

    generateSQLParts(sqlHead, sqlBatch, sqlUpdate, mode);
    sqlTail = generateSQLTail(sqlBatch, sqlUpdate, batchsize, mode);

    _connection.prepareStatement(sqlHead + sqlTail);

    int paramNum = 0;    
    for (unsigned int i = 0; i < models.size(); i++) {
        Model * m = models[i];
        
        for (unsigned int j = 0; j < m->fields.size(); j++) {
            Field * f = m->fields[j];

            if (f->isAutoFilled() == false) {
                paramNum++;

                if (f->isNull()) {
                    _connection.setNull(paramNum);
                } else {
                    f->setParameter(paramNum, _connection);
                }
            }
        }

        // when we reach the batch size, execute the current statement and prepare the next
        if (i+1 % batchsize == 0) {
            _connection.executeStatement();

            paramNum = 0;

            if (i+1 >= finalBatchStartIndex) {
                batchsize = finalBatchSize;
                sqlTail = generateSQLTail(sqlBatch, sqlUpdate, batchsize, mode);
            }

            _connection.deleteStatement();
            _connection.prepareStatement(sqlHead + sqlTail);
        }
    }

    return 0;
}

int Model::truncate() {
    _connection.prepareStatement("TRUNCATE " + tableName);
    _connection.executeStatement();
    _connection.deleteStatement();

    return 0;
}

int Model::createTable() {
    string sql = "CREATE TABLE IF NOT EXISTS " + tableName;

    sql += " (";

    string primaryKey = "";
    for (unsigned int i = 0; i < fields.size(); i++) {
        Field * f = fields[i];
        sql += f->generateColumnSQL();

        if (i < fields.size() - 1) {
            sql += ", ";
        }
    }

    sql += primaryKey + ");";

    _connection.prepareStatement(sql);
    _connection.executeStatement();
    _connection.deleteStatement();

    return 0;
}

int Model::dropTable() {
    string sql = "DROP TABLE IF EXISTS " + tableName;

    _connection.prepareStatement(sql);
    _connection.executeStatement();
    _connection.deleteStatement();

    return 0;
}

int Model::setConnection(DBConnection connection) {
    _connection = connection;
    return 0;
}

DBConnection Model::getConnection() {
    return _connection;
}

void Model::generateSQLParts(string &sqlHead, string &sqlBatch, string &sqlUpdate, Mode mode) {
    string sqlFields = "";
    sqlBatch = "(";
    sqlUpdate = " ON DUPLICATE KEY UPDATE ";

    bool isFirstField = true;

    for (unsigned int i = 0; i < fields.size(); i++) {
        Field* f = fields[i];

        if (!f->isAutoFilled()) {
            if (isFirstField) {
                isFirstField = false;

                sqlFields += f->getName();
                sqlBatch += "?";

                if (mode == UPDATE) {
                    sqlUpdate += f->getName() + " = VALUES(" + f->getName() + ")";
                }
            } else {
                sqlFields += ", " + f->getName();
                sqlBatch += ",?";

                if (mode == UPDATE) {
                    sqlUpdate += ", " + f->getName() + " = VALUES(" + f->getName() + ")";
                }
            }
        }
    }

    sqlBatch += ")";

    if (mode == IGNORE) {
        sqlHead = "INSERT IGNORE INTO " + tableName + " (" + sqlFields + ") VALUES ";
    } else {
        sqlHead = "INSERT INTO " + tableName + " (" + sqlFields + ") VALUES ";
    }
}

string Model::generateSQLTail(string &sqlBatch, string &sqlUpdate, int batchsize, Mode mode) {
    string sqlTail = sqlBatch;

    for (int j = 1; j < batchsize; j++) {
        sqlTail += "," + sqlBatch;
    }

    if (mode == UPDATE) {
        sqlTail += sqlUpdate;
    }

    return sqlTail;
}
