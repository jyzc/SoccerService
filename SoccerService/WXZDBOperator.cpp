#include "stdafx.h"
#include "WXZDBOperator.h"
#include "MysqlOperator.h"

DBOperator::DBOperator()
{

}

DBOperator::~DBOperator()
{

}

//////////////////////////////////////////////////////////////////////////
//获得今天比赛数据
void DBOperator::getTodayList(vector<Match*>& matchList)
{
// 	map<string,string> config = conf.get_config();  
// 	mysql_database db (config);  
// 	db.db_connect();  
// 	sql::ResultSet * rs;  
// 	map<string,string> field ;  
// 	field["0"]="v_name" ;//  
// 	rs=db.query("select v_name  from  pi_data  limit 1 ");  
// 	map<int,map<string,string> > rows;  
// 	rows = db.fetch_map(rs,field);  
// 	map<int,map<string,string> >::iterator  it;  
// 	for (it = rows.begin(); it != rows.end(); it++)  
// 	{  
// 		map<string,string>::iterator item;  
// 		map<string,string> content;  
// 		content=it->second;  
// 		for (item = content.begin(); item != content.end(); item++)  
// 		{  
// 			cout << item->second << endl;  
// 		}  
// 	}  
}

//更新数据入库
bool DBOperator::updateData(const vector<Match*> matchList)
{
	return false;
}