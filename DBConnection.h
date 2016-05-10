#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include "mysql_connection.h"
#include <cppconn/resultset.h>

using namespace std;

class DBConnection
{
	public:		
		//Data Access Methods
		int prepareStatement(string sql);
		int deleteStatement();
		int executeStatement(int numRetries = 2);
		
		sql::ResultSet* executeQuery(int numRetries = 2);
		
		void setString(int paramNum, string value);
		void setInt(int paramNum, int value);
		void setDouble(int paramNum, double value);
		void setNull(int paramNum);
		
		//DB Connection Methods
		int setConnection(sql::Connection **connection);
		int connectDB(string host, string user, string password, string schema);
		int resetConnection();
		int closeConnection();
		
	
	private:
		//Connection Variables
		sql::Connection *conn;
		sql::PreparedStatement *prep_stmt;
	    
	    string h, u, p, s;
	    
		int connect();
};

#endif