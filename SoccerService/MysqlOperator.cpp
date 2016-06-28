#include "stdafx.h"
#include "MysqlOperator.h"

#include <cppconn/driver.h>  
#include <cppconn/exception.h>  
#include <cppconn/statement.h>  
#include <cppconn/prepared_statement.h>  
#include <stdlib.h> 
#include <iostream>  

#include "Settings.h"
#include "Util.h"

#pragma comment(lib, "mysqlcppconn-static.lib")
/*
http://blog.csdn.net/sunylat/article/details/8480127
http://dev.mysql.com/tech-resources/articles/mysql-connector-cpp.html#trx
http://blog.sina.com.cn/s/blog_86fe5b440102v3mz.html
http://developer.51cto.com/art/201104/257338.htm

http://blog.csdn.net/youngqj/article/details/8281182
*/

mysql_database::mysql_database()
{

}

mysql_database::~mysql_database()
{
	db_close();
}

mysql_database::mysql_database(map<string,string> &conf) :  
driver_(NULL), con_(NULL), stmt_(NULL), result_(NULL)  
{  
	db_host = conf["db_host"];  
	db_name = conf["db_name"];  
	db_user = conf["db_user"];  
	db_passwd = conf["db_passwd"];  
	db_port = conf["db_port"];  
	db_charset = conf["db_charset"]; 

	isConnect_ = false;
}  

mysql_database::mysql_database(DBSettings& settings):
	driver_(NULL), con_(NULL), stmt_(NULL), result_(NULL)  
{
	db_host = settings.dbHost();  
	db_name = settings.dbName();  
	db_user = settings.dbUser();  
	db_passwd =settings.dbPwd();  
	db_port = settings.dbPort();  

}

//////////////////////////////////////////////////////////////////////////
sql::Connection* mysql_database::db_connect(string database)
{
	try{  
		std::string db = "";  
		db = (database=="") ? db_name:database;  
		driver_ = get_driver_instance();  
// 		cout<<db_host<<db_port<<db_user<<db_passwd<<db_name<<endl; 
		std::string hostName = "tcp://"+db_host+":"+db_port;
		con_ = driver_->connect(hostName.c_str(), db_user.c_str(), db_passwd.c_str());  
// 		con = driver->connect("tcp://127.0.0.1:3306", "root", "123456");
		con_->setSchema(db.c_str());  
// 		this->squery("SET NAMES "+db_charset);  
		return con_;  
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

void mysql_database::db_close()
{
	if (isConnect_)
	{
		isConnect_ = false;
		if (stmt_)
			delete stmt_;
		if (con_)
		{
			con_->close();
			delete con_;
		}
	}
}
/** 
* simple query for  create/update/delete 
* @param string sql 
* @return bool  TRUE OR FALS 
*/  
bool mysql_database::squery(string sql)  
{  
    stmt_ = con_->createStatement();  
    return stmt_->execute(sql.c_str());  
}  
sql::ResultSet * mysql_database::query(string sql)  
{  
    stmt_ = con_->createStatement();  
    result_ = stmt_->executeQuery(sql.c_str());  
    return result_;  
}  
int mysql_database::insert(std::string sql)
{
	stmt_ = con_->createStatement();  
	return stmt_->executeUpdate(sql.c_str());
}

int mysql_database::multi_insert(std::string tableName, std::map<string, string>field)
{
// 	PreparedStatement *ps = con_.prepareStatement("insert into tb_name(col1,col2,col2,col4) values (?,?,?,?)");
// 	ps->setInt64()
// 	ps->executeUpdate();
	return 0;
}


/* retrieve the row count in the result set */  
int mysql_database::get_total(sql::ResultSet *result)  
{  
	return result->rowsCount();  
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
				{
					row[it->first] = result->getString(it->second.c_str()).c_str(); 
				}
                data[k]=row;  
                k++;  
        }  
    }  
  
    return data ;  
}  