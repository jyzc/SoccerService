#ifndef _PARSE_FILE_BFDATA_H__
#define _PARSE_FILE_BFDATA_H__
#pragma once

class Match;

class ParseFileBfdata
{
public:
	ParseFileBfdata();
	~ParseFileBfdata();

	void parseMatchList(const wstring & matchRecord, vector<Match*>& matchList);
private:
	int getMatchCount(const wstring & str);
	Match* getMatch(const wstring & str);
 	time_t getMatchDate(const wstring & year, const wstring & monthDay, const wstring & hourMinute);
};




#endif	//_PARSE_FILE_BFDATA_H__