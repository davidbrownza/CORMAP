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
    _preparedStatement = _connection->prepareStatement(sql);
    return 0;
}

int DBConnection::deleteStatement() {
    delete _preparedStatement;
    return 0;
}

int DBConnection::executeStatement() {
    _preparedStatement->execute();
    return 0;
}

sql::ResultSet* DBConnection::executeQuery() {
    sql::ResultSet *res;
    res = _preparedStatement->executeQuery();
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

    _connection = driver->connect(_host, _user, _password);
    _connection->setSchema(_schema);

    return 0;
}

void DBConnection::setString(int parameterNumber, string value) {
    _preparedStatement->setString(parameterNumber, value);
}

void DBConnection::setInt(int parameterNumber, int value) {
    _preparedStatement->setInt(parameterNumber, value);
}

void DBConnection::setDouble(int parameterNumber, double value) {
    _preparedStatement->setDouble(parameterNumber, value);
}

void DBConnection::setBlob(int parameterNumber, istream &value) {
    _preparedStatement->setBlob(parameterNumber, value);
}

void DBConnection::setNull(int parameterNumber) {
    _preparedStatement->setNull(parameterNumber, 0);
}

int DBConnection::setConnection(sql::Connection **connection) {
    _connection = *connection;
    return 0;
}

int DBConnection::closeConnection() {
    delete _connection;
    return 0;
}

int DBConnection::resetConnection() {
    closeConnection();
    return connect();
}
