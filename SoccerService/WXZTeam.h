#ifndef _TEAM_H__
#define _TEAM_H__
#pragma once


//���������
class TeamData
{
public:
	TeamData();
	~TeamData();


private:

};


//�����
class Team
{
public:
	Team();
	~Team();

	void setId(const long & id) {id_ = id;}
	const long & id() {return id_;}	
	void setName(const wstring & name) {name_ = name;}
	const wstring & name() {return name_;} 


private:
	long id_;		//���ID
	wstring name_;	//�������
};

#endif 	//_TEAM_H__