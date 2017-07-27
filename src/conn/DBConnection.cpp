#include "DBConnection.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

//Data Access Methods
int DBConnection::prepareStatement(string sql) {    
    _prep_stmt = _conn->prepareStatement(sql);
    return 0;
}

int DBConnection::deleteStatement() {
    delete _prep_stmt;    
    return 0;
}

int DBConnection::executeStatement() {
    _prep_stmt->execute(); 
    return 0;
}

sql::ResultSet* DBConnection::executeQuery() {
    sql::ResultSet *res;
    res = _prep_stmt->executeQuery(); 
    return res;
}
        
//DB Connection Methods
int DBConnection::connectDB(string host, string user, string password, string schema) {    
    _host = host;
    _user = user;
    _password = password;
    _schema = schema;
          
    return connect();
}

int DBConnection::connect() {
    sql::Driver *driver;
    driver = get_driver_instance();
    
    _conn = driver->connect(_host, _user, _password);
    _conn->setSchema(_schema);
    
    return 0;
}

void DBConnection::setString(int parameterNumber, string value) {
    _prep_stmt->setString(parameterNumber, value);
}

void DBConnection::setInt(int parameterNumber, int value) {
    _prep_stmt->setInt(parameterNumber, value);
}

void DBConnection::setDouble(int parameterNumber, double value) {
    _prep_stmt->setDouble(parameterNumber, value);
}

void DBConnection::setNull(int parameterNumber) {
    _prep_stmt->setNull(parameterNumber, 0);
}

int DBConnection::setConnection(sql::Connection **connection) {    
    _conn = *connection;
    return 0;
}

int DBConnection::closeConnection() {
    delete _conn;
    return 0;
}

int DBConnection::resetConnection() {
    closeConnection();
    return connect();
}
