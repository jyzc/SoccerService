#ifndef _PARSE_FILE_BFDATA_H__
#define _PARSE_FILE_BFDATA_H__
#pragma once

class Match;

class ParseFileBfdata
{
public:
	ParseFileBfdata();
	~ParseFileBfdata();

	void parseMatchList(const wstring matchRecord, vector<Match*>& matchList);
private:
	int getMatchCount(wstring str);
	Match* getMatch(wstring str);

};




#endif	//_PARSE_FILE_BFDATA_H__