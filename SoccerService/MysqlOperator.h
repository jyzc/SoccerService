#ifndef _MYSQL_DATABASE_H__
#define _MYSQL_DATABASE_H__
#pragma once

#include <map>
#include "mysql_connection.h" 
#include <cppconn/sqlstring.h>
#include <cppconn/resultset.h>  
using namespace std;  

class DBSettings;

class mysql_database
{
public:
	mysql_database();
	mysql_database(DBSettings& settings);
	mysql_database(map<string,string> &conf);
	~mysql_database();

	sql::Connection* db_connect(string database = "");
	void db_close();

	int insert(std::string sql);
	int multi_insert(std::string tableName, std::map<string, string>field);

	int get_total(sql::ResultSet *result)  ;
	sql::ResultSet *query(string sql) ;
	bool squery(string sql);
	map<int,map<string,string> > fetch_map(sql::ResultSet *result, map<string,string>field)  ;

	bool isConnect() {return isConnect_;};
private:  
	std::string  db_host;  
	std::string  db_name;  
	std::string  db_user;  
	std::string  db_passwd;  
	std::string  db_charset;  
	std::string  db_port;  

	sql::Driver *driver_;  
	sql::Connection *con_;  
	sql::Statement *stmt_;  
	sql::ResultSet *result_;  

	bool isConnect_;
};


#endif	//_MYSQL_DATABASE_H__