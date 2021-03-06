#ifndef _NET_REQUEST_H__
#define _NET_REQUEST_H__
#pragma once

class Match;
class Http;

class NetRequest
{
public:
	NetRequest();
	~NetRequest();

	const Http* http(){return http_;}

	//获得比赛基本信息matchList
	void getMatchList(vector<Match*>& matchList);
	//获得比赛对战数据
	bool getMatchData(Match* matchList);
protected:
private:
	void setHttp(Http* http){ http_ = http;}

	Http* http_;
// 	int requestCount_;//请求次数
};


#endif	//_NET_REQUEST_H__
