#ifndef _EVENT_H__
#define _EVENT_H__
#pragma once

//赛事类
class Event
{
public:
	Event();
	~Event();


	void setId(const long & id) {id_ = id;}
	const long & id() {return id_;}	
	void setName(const wstring & name) {name_ = name;}
	const wstring & name() {return name_;} 


private:
	long id_;			//赛事ID
	wstring name_;		//赛事名称

};

#endif 	//_EVENT_H__