#ifndef _PARSE_H__
#define _PARSE_H__
#pragma once

using namespace std;

class Match;

class Parse
{
public:
	Parse();
	~Parse();

	//解析比赛列表
	void parseMatchList(const wstring matchRecord, vector<Match*>& matchList);
	//解析战绩数据
	void parseMatchRecord(const wstring matchRecord, Match* matchList);
private:


};

#endif //_PARSE_H__
