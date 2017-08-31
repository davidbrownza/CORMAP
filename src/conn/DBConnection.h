#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include "mysql_connection.h"
#include <cppconn/resultset.h>

using namespace std;

class DBConnection {

    public:
        //Data Access Methods
        int prepareStatement(string sql);
        int deleteStatement();

        int executeStatement();
        sql::ResultSet* executeQuery();

        void setString(int parameterNumber, string value);
        void setInt(int parameterNumber, int value);
        void setDouble(int parameterNumber, double value);
        void setBlob(int parameterNumber, istream &value);
        void setNull(int parameterNumber);

        //DB Connection Methods
        int setConnection(sql::Connection **connection);
        int connectDB(string host, string user, string password, string schema);
        int resetConnection();
        int closeConnection();


    private:
        //Connection Variables
        sql::Connection *_connection;
        sql::PreparedStatement *_preparedStatement;

        string _host, _user, _password, _schema;

        int connect();
};

#endif
