#ifndef _TEAM_H__
#define _TEAM_H__
#pragma once


//球队数据类
class TeamData
{
public:
	TeamData();
	~TeamData();


private:

};


//球队类
class Team
{
public:
	Team();
	~Team();

	void setId(const long & id) {id_ = id;}
	const long & id() {return id_;}	
	void setName(const string & name) {name_ = name;}
	const string & name() {return name_;} 


private:
	long id_;		//球队ID
	string name_;	//球队名称
};

#endif 	//_TEAM_H__