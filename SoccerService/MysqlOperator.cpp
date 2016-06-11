#include "stdafx.h"
#include "MysqlOperator.h"

#include <cppconn/driver.h>  
#include <cppconn/exception.h>  
#include <cppconn/statement.h>  
#include <cppconn/prepared_statement.h>  
#include <stdlib.h> 
#include <iostream>  
#pragma comment(lib, "mysqlcppconn-static.lib")

mysql_database::mysql_database()
{

}

mysql_database::~mysql_database()
{

}

mysql_database::mysql_database(map<string,string> &conf) :  
driver(NULL),con(NULL),stmt(NULL),result(NULL)  
{  
	db_host = conf["db_host"];  
	db_name = conf["db_name"];  
	db_user = conf["db_user"];  
	db_passwd = conf["db_passwd"];  
	db_port = conf["db_port"];  
	db_charset = conf["db_charset"];  
}  

//////////////////////////////////////////////////////////////////////////
sql::Connection* mysql_database::db_connect(string database)
{
	try{  
		string db;  
		db = (database=="") ? db_name:database;  
		driver = get_driver_instance();  
		//cout<<db_host<<db_port<<db_user<<db_passwd<<db_name<<endl;  
		con = driver->connect("tcp://"+db_host+":"+db_port, db_user, db_passwd);  
		con->setSchema(db);  
// 		this->squery("SET NAMES "+db_charset);  
		return con;  
	}  
	catch (sql::SQLException &e)  
	{  
		cout << "# ERR: SQLException in " << __FILE__;  
		cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;  
		cout << "# ERR: " << e.what();  
		cout << " (MySQL error code: " << e.getErrorCode();  
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;  
	}  
	return 0;
}

/** 
* simple query for  create/update/delete 
* @param string sql 
* @return bool  TRUE OR FALS 
*/  
bool mysql_database::squery(string sql)  
{  
    stmt = con->createStatement();  
    return stmt->execute(sql);  
}  
sql::ResultSet * mysql_database::query(string sql)  
{  
    stmt = con->createStatement();  
    result=stmt->executeQuery(sql);  
    return result;  
}  
/* retrieve the row count in the result set */  
int mysql_database::get_total(sql::ResultSet *result)  
{  
    int total;  
    total=result->rowsCount();  
    return total;  
} 

/** 
* fetch query rows 
* @param result 
* @param field          the db table's field for this query 
* @return mutil_map      
*/  
map<int,map<string,string> > mysql_database::fetch_map(sql::ResultSet *result,map<string,string>field)  
{  
    /* fetch the data : retrieve all the rows in the result set */  
    map<int,map<string,string> > data;  
    map<string,string>::iterator  it;  
    int k=0;  
    if((!field.empty())&&(field.size()>0))  
    {  
        while(result->next())  
        {  
                map<string,string> row;  
                for ( it=field.begin() ; it!=field.end() ;it++ )  
                        row[it->first]=result->getString(it->second);  
                data[k]=row;  
                k++;  
        }  
    }  
  
    return data ;  
}  