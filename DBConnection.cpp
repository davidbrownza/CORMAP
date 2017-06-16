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
int DBConnection::prepareStatement(string sql)
{	
	prep_stmt = conn->prepareStatement(sql);
	
	return 0;
}

int DBConnection::deleteStatement()
{
	delete prep_stmt;	
	
	return 0;
}

int DBConnection::executeStatement()
{
	prep_stmt->execute(); 
	
	return 0;
}

sql::ResultSet* DBConnection::executeQuery()
{
	sql::ResultSet *res;
	res = prep_stmt->executeQuery(); 
	return res;
}
		
//DB Connection Methods
int DBConnection::connectDB(string host, string user, string password, string schema)
{	
    h = host;
    u = user;
    p = password;
    s = schema;
	  	
	return connect();
}

int DBConnection::connect() {
    sql::Driver *driver;
	driver = get_driver_instance();
	
	conn = driver->connect(h, u, p);
	  	
	conn->setSchema(s);
	
	return 0;
}

void DBConnection::setString(int paramNum, string value)
{
	prep_stmt->setString(paramNum, value);
}

void DBConnection::setInt(int paramNum, int value)
{
	prep_stmt->setInt(paramNum, value);
}

void DBConnection::setDouble(int paramNum, double value)
{
	prep_stmt->setDouble(paramNum, value);
}

void DBConnection::setNull(int paramNum)
{
	prep_stmt->setNull(paramNum, 0);
}

int DBConnection::setConnection(sql::Connection **connection)
{	
	conn = *connection;
	
	return 0;
}

int DBConnection::closeConnection()
{
	delete conn;
	
	return 0;
}

int DBConnection::resetConnection()
{
    closeConnection();
    return connect();
}
