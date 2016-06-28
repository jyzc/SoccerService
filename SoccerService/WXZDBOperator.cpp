#include "stdafx.h"
#include "WXZDBOperator.h"
#include "MysqlOperator.h"
#include "Settings.h"
#include "WXZMatch.h"
#include "WXZTeam.h"
#include "Util.h"

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
	if (!dbSettings_->isLoad())
		dbSettings_->loadFile("Settings.ini");
	
	mysql_database db (*dbSettings_);  
	db.db_connect();  
	sql::ResultSet * rs;  
	map<string,string> field ;  
	field["MATCH_ID"]="MATCH_ID" ;//  
	field["PARAMETER_FULLY"]="PARAMETER_FULLY";//  
	field["MATCH_STATUS"]="MATCH_STATUS";//  

	rs=db.query("select *  from  T_MATCH");  
	map<int,map<string,string> > rows;  
	rows = db.fetch_map(rs,field);  
	map<int,map<string,string> >::iterator  it;  
	for (it = rows.begin(); it != rows.end(); it++)  
	{  
// 		map<string,string>::iterator item;  
		map<string,string> content;  
		content=it->second;  
		string s = content["MATCH_ID"];
// 		for (item = content.begin(); item != content.end(); item++)  
// 		{  
// 			cout << item->second << endl;  
// 		}  
		Match* pNew = new Match();
		pNew->setId(mbs_to_l(s));
		matchList.push_back(pNew);
	}  
}

//更新数据入库
bool DBOperator::updateData(const vector<Match*> matchList)
{
	if (matchList.size()<=0)
		return true;

	if (!dbSettings_->isLoad())
		dbSettings_->loadFile("Settings.ini");

	mysql_database db (*dbSettings_);  
	db.db_connect(); 
	for (int i=0; i<(int)matchList.size(); i++)
	{
		Match* pMatch = matchList[i];
		if (pMatch)
		{
			std::string execSql = "";
			execSql = "SELECT * FROM T_TEAM WHERE TEAM_ID=" + l_to_mbs(pMatch->homeTeam()->id());
			sql::ResultSet * rs = db.query(execSql);
			if (rs && rs->rowsCount()<=0)
			{
				execSql = "INSERT INTO T_TEAM (TEAM_ID, TEAM_NAME) VALUES (" + l_to_mbs(pMatch->homeTeam()->id()) + ",'" + wcs_to_mbs(pMatch->homeTeam()->name(), std::locale(""))+"')";
				db.squery(execSql);
			}

			execSql = "SELECT * FROM T_TEAM WHERE TEAM_ID=" + l_to_mbs(pMatch->guestTeam()->id());
			rs = db.query(execSql);
			if (rs && rs->rowsCount()<=0)
			{
				execSql = "INSERT INTO T_TEAM (TEAM_ID, TEAM_NAME) VALUES (" + l_to_mbs(pMatch->homeTeam()->id()) + ",'" + wcs_to_mbs(pMatch->homeTeam()->name(), std::locale(""))+"')";
				db.squery(execSql);
			}

		}
	}






	sql::ResultSet * rs;  
	map<string,string> field ;  
	field["MATCH_ID"]="MATCH_ID" ;//  
	field["PARAMETER_FULLY"]="PARAMETER_FULLY";//  
	field["MATCH_STATUS"]="MATCH_STATUS";//  

	rs=db.query("select *  from  T_MATCH");  
	map<int,map<string,string> > rows;  
	rows = db.fetch_map(rs,field);  
	map<int,map<string,string> >::iterator  it;  
	for (it = rows.begin(); it != rows.end(); it++)  
	{  
		// 		map<string,string>::iterator item;  
		map<string,string> content;  
		content=it->second;  
		string s = content["MATCH_ID"];
// 		for (item = content.begin(); item != content.end(); item++)  
// 		{  
// 			cout << item->second << endl;  
// 		}  
	}
	return false;
}