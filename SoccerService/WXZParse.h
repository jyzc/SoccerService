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

	//���������б�
	void parseMatchList(const wstring matchRecord, vector<Match*>& matchList);
	//����ս������
	void parseMatchRecord(const wstring matchRecord, Match* matchList);
private:


};

#endif //_PARSE_H__
