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

	//��ñ���������ϢmatchList
	void getMatchList(vector<Match*>& matchList);
	//��ñ�����ս����
	bool getMatchData(Match* matchList);
protected:
private:
	void setHttp(Http* http){ http_ = http;}

	Http* http_;
// 	int requestCount_;//�������
};


#endif	//_NET_REQUEST_H__
