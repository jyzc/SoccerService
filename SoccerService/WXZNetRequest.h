#ifndef _NET_REQUEST_H__
#define _NET_REQUEST_H__
#pragma once

class Match;

class NetRequest
{
public:
	NetRequest();
	~NetRequest();

	//获得比赛基本信息matchList
	void getMatchList(vector<Match*>& matchList);
	//获得比赛对战数据
	void getMatchData(Match* matchList);
protected:
private:
};


#endif	//_NET_REQUEST_H__
