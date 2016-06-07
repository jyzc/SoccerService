#ifndef _PARSE_FILE_ANALYSIS_H__
#define _PARSE_FILE_ANALYSIS_H__
#pragma once

class Match;

class ParseFileAnalysis
{
public:
	ParseFileAnalysis();
	~ParseFileAnalysis();

	void parseMatchRecord(const wstring matchRecord, Match* matchList);
private:
	Match* getRecord(const wstring matchRecord);
	void getRecords(const wstring matchRecord, vector<Match*>& homeRecord);
	void getJiaoFengRecord(const wstring matchRecord, vector<Match*>& jiaoFeng, vector<Match*> &jiaoFengSame, long homeId, long guestId);

	time_t getTime(const wstring value);
	wstring getName(const wstring value);
	void getHarfScore(const wstring value, BYTE& homeScore, BYTE& guestScore);
// 	void getHomeRecord(const wstring matchRecord, vector<Match*>& homeRecord);
// 	void getHomeRecordSame(const wstring matchRecord, vector<Match*>& homeRecordSame);
// 	void getGuestRecord(const wstring matchRecord, vector<Match*>& guestRecord);
// 	void getGuestRecordSame(const wstring matchRecord, vector<Match*>& homeRecordSame);
};




#endif