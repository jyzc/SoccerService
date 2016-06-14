#ifndef _DB_OPERATOR_H__
#define _DB_OPERATOR_H__
#pragma once

class Match;
class DBSettings;

class DBOperator
{
public:
	DBOperator();
	~DBOperator();

	//获得今天比赛数据
	void getTodayList(vector<Match*>& matchList);
	//更新数据入库
	bool updateData(const vector<Match*> matchList);

private:
	DBSettings* dbSettings_;

};


#endif	//_DB_OPERATOR_H__