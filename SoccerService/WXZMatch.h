#ifndef _MATCH_H__
#define _MATCH_H__
#pragma once

#include <time.h>		/*time_t*/
#include <vector>
using namespace std;

class Team;
class Event;

//比赛类
class Match
{
public:
	enum MatchStatus{
		DELAY=-14,
		INTERRUPTION=-12,//interruption 
		NOSTART=0,
		FIRSTHARF=1,
		HARFTIME=2,
		SECONDHARF=3
	};

public:
	Match();
	~Match();

	bool checkMatch();

	void setId(const long & id) {id_ = id;}
	const long & id() {return id_;}	
	void setDate(const time_t & date) { date_ = date;}
	const time_t & date() {return date_;}
	void setResult(const BYTE & result) {result_ = result;}
	const BYTE & result() {return result_;}
	void setStatus(const int & status) {status_ = status;}
	const int & status() {return status_;}	
	void setHomeScore(const BYTE & homeScore) {homeScore_ = homeScore;}
	const BYTE & homeScore() {return homeScore_;}	
	void setGuestScore(const BYTE & guestScore) {guestScore_ = guestScore;}
	const BYTE & guestScore() {return guestScore_;}	
	void setHomeScoreHarf(const BYTE & homeScoreHarf) {homeScoreHarf_ = homeScoreHarf;}
	const BYTE & homeScoreHarf() {return homeScoreHarf_;}	
	void setGuestScoreHarf(const BYTE & guestScoreHarf) {guestScoreHarf_ = guestScoreHarf;}
	const BYTE & guestScoreHarf() {guestScoreHarf_;}

	void setHomeTeam(Team* homeTeam) {homeTeam_ = homeTeam;}
	Team* homeTeam() const {return homeTeam_;}
	void setGuestTeam(Team* guestTeam) {guestTeam_ = guestTeam;}
	Team* guestTeam() const {return  guestTeam_;}
	void setEvent(Event* event) {event_ = event;}
	Event* event() const {return event_;}


	void setJiaoFengRecord(vector<Match*> & jiaoFengRecord);
	vector<Match*> jiaoFengRecord(){return jiaoFengRecord_;}
	void setJiaoFengRecordSame(vector<Match*> & jiaoFengRecordSame);
	vector<Match*> jiaoFengRecordSame(){return jiaoFengRecordSame_;}

	void setHomeRecord(vector<Match*> & homeRecord);
	vector<Match*> homeRecord(){return homeRecord_;}
	void setHomeRecordSame(vector<Match*> & homeRecordSame);
	vector<Match*> homeRecordSame(){return homeRecordSame_;}
	void setGuestRecord(vector<Match*> & guestRecord);
	vector<Match*> guestRecord(){return guestRecord_;}
	void setGuestRecordSame(vector<Match*> & guestRecordSame);
	vector<Match*> guestRecordSame(){return guestRecordSame_;}

private:
	long id_;				//比赛ID
	time_t date_;			//比赛时间
	BYTE result_;			//比赛结果 -14推迟,-12腰斩,-11,-10;-1完成; 0未开赛; 1上半场;2中场;3下半场;
	int status_;	//比赛状态	
	BYTE homeScore_;		//主队进球
	BYTE guestScore_;		//客队进球
	BYTE homeScoreHarf_;	//主队上半进球
	BYTE guestScoreHarf_;	//客队上半进球

	Team* homeTeam_;		//主队
	Team* guestTeam_;		//客队
	Event* event_;			//赛事

	vector<Match*> jiaoFengRecord_;			//交锋记录
	vector<Match*> jiaoFengRecordSame_;		//主客相同交锋记录
	vector<Match*> homeRecord_;				//主队记录
	vector<Match*> homeRecordSame_;			//主队主场记录
	vector<Match*> guestRecord_;			//客队记录
	vector<Match*> guestRecordSame_;		//客队客场记录
};

#endif 	//_MATCH_H__
