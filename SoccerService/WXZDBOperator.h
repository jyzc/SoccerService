#ifndef _DB_OPERATOR_H__
#define _DB_OPERATOR_H__
#pragma once

class Match;

class DBOperator
{
public:
	DBOperator();
	~DBOperator();

	//��ý����������
	void getTodayList(vector<Match*>& matchList);
	//�����������
	bool updateData(const vector<Match*> matchList);

private:

};


#endif	//_DB_OPERATOR_H__