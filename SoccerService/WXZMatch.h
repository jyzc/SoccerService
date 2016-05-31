#ifndef _MATCH_H__
#define _MATCH_H__
#pragma once

#include <time.h>		/*time_t*/


class Team;
class Event;

//比赛类
class Match
{
public:
	enum MatchStatus{
		IDLE=0,
		BEGIN=1
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
	void setStatus(const MatchStatus & status) {status_ = status;}
	const MatchStatus & status() {return status_;}	
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

private:
	long id_;				//比赛ID
	time_t date_;			//比赛时间
	BYTE result_;			//比赛结果 0，1，3
	MatchStatus status_;	//比赛状态	
	BYTE homeScore_;		//主队进球
	BYTE guestScore_;		//客队进球
	BYTE homeScoreHarf_;	//主队上半进球
	BYTE guestScoreHarf_;	//客队上半进球

	Team* homeTeam_;		//主队
	Team* guestTeam_;		//客队
	Event* event_;			//赛事

};

#endif 	//_MATCH_H__
