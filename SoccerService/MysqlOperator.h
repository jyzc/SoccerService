#ifndef _MYSQL_DATABASE_H__
#define _MYSQL_DATABASE_H__
#pragma once

#include <map>
#include "mysql_connection.h"  
#include <cppconn/resultset.h>  
using namespace std;  

class mysql_database
{
public:
	mysql_database();
	mysql_database(map<string,string> &conf);
	~mysql_database();

	sql::Connection* db_connect(string database = "");

	int get_total(sql::ResultSet *result)  ;
	sql::ResultSet *query(string sql) ;
	bool squery(string sql)  ;
	map<int,map<string,string> > fetch_map(sql::ResultSet *result, map<string,string>field)  ;

private:  
	string  db_host;  
	string  db_name;  
	string  db_user;  
	string  db_passwd;  
	string  db_charset;  
	string  db_port;  

	sql::Driver *driver;  
	sql::Connection *con;  
	sql::Statement *stmt;  
	sql::ResultSet *result;  
};


#endif	//_MYSQL_DATABASE_H__