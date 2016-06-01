#ifndef _TEAM_H__
#define _TEAM_H__
#pragma once


//球队数据类
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
	int		jiFen_;		//当前积分
	int		paiHang_;	//当前排行
	int		finishNum_;	//已赛场次
	int		shengNum_;	//胜场次
	int		fuNum_;		//负场次
	int		pingNum_;	//平场次
	int		jinQiu_;	//进球
	int		shiQiu_;	//失球

	time_t	ttNow_;		//当前时间
};


//球队类
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
	long id_;		//球队ID
	wstring name_;	//球队名称
	LeagueData* leagueData_;//球队数据
};

#endif 	//_TEAM_H__