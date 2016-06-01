#ifndef _TEAM_H__
#define _TEAM_H__
#pragma once


//���������
class LeagueData
{
public:
	LeagueData();
	~LeagueData();


	void setJiFen(const int & jiFen) {jiFen_ = jiFen;}
	const int & jiFen() {return jiFen_;}	
	void setPaiHang(const int & paiHang) {paiHang_ = paiHang;}
	const int & paiHang() {return paiHang_;}
	void setFinishNum(const int & finishNum) {finishNum_ = finishNum;}
	const int & finishNum() {return finishNum_;}
	void setShengNum(const int & shengNum) {shengNum_ = shengNum;}
	const int & shengNum() {return shengNum_;}	
	void setFuNum(const int & fuNum) {fuNum_ = fuNum;}
	const int & fuNum() {return fuNum_;}
	void setPingNum(const int & pingNum) {pingNum_ = pingNum;}
	const int & pingNum() {return pingNum_;}	
	void setJinQiu(const int & jinQiu) {jinQiu_ = jinQiu;}
	const int & jinQiu() {return jinQiu_;}	
	void setShiQiu(const int & shiQiu) {shiQiu_ = shiQiu;}
	const int & shiQiu() {return shiQiu_;}	


private:
	int		jiFen_;		//��ǰ����
	int		paiHang_;	//��ǰ����
	int		finishNum_;	//��������
	int		shengNum_;	//ʤ����
	int		fuNum_;		//������
	int		pingNum_;	//ƽ����
	int		jinQiu_;	//����
	int		shiQiu_;	//ʧ��

	time_t	ttNow_;		//��ǰʱ��
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
	void setLeagueData(LeagueData* leagueData) {leagueData_=leagueData;}
	LeagueData* leagueData(){return  leagueData_;}

private:
	long id_;		//���ID
	wstring name_;	//�������
	LeagueData* leagueData_;//�������
};

#endif 	//_TEAM_H__