#ifndef _EVENT_H__
#define _EVENT_H__
#pragma once

//������
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
	long id_;			//����ID
	wstring name_;		//��������

};

#endif 	//_EVENT_H__