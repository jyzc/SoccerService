#ifndef _NET_REQUEST_H__
#define _NET_REQUEST_H__
#pragma once

class Match;

class NetRequest
{
public:
	NetRequest();
	~NetRequest();

	//��ñ���������ϢmatchList
	void getMatchList(vector<Match*>& matchList);
	//��ñ�����ս����
	void getMatchData(Match* matchList);
protected:
private:
};


#endif	//_NET_REQUEST_H__
