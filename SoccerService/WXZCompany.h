#ifndef _COMPANY_H__
#define _COMPANY_H__
#pragma once
using namespace std;

class Company
{
public:
	Company();
	~Company();

	void setId(const long & id) {id_ = id;}
	const long & id() {return id_;}	
	void setName(const string & name) {name_ = name;}
	const string & name() {return name_;} 


private:

	long id_;		//���ʹ�˾ID
	string name_;	//���ʹ�˾����
};



#endif 	//_COMPANY_H__