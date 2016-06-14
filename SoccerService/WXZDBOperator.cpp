#include "stdafx.h"
#include "WXZDBOperator.h"
#include "MysqlOperator.h"
#include "Settings.h"

// #pragma warning(disable:4251) 

DBOperator::DBOperator()
{
	dbSettings_ = new DBSettings();
}

DBOperator::~DBOperator()
{
	if (dbSettings_)
		delete dbSettings_;

}

//////////////////////////////////////////////////////////////////////////
//获得今天比赛数据
void DBOperator::getTodayList(vector<Match*>& matchList)
{
	dbSettings_->loadFile("Settings.ini");
	
// 	map<string,string> config = conf.get_config();  
	mysql_database db (*dbSettings_);  
	db.db_connect();  
	sql::ResultSet * rs;  
	map<string,string> field ;  
	field["0"]="TEAM_ID" ;//  
	rs=db.query("select *  from  T_Team  limit 1 ");  
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