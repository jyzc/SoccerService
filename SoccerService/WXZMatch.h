#ifndef _MATCH_H__
#define _MATCH_H__
#pragma once

#include <time.h>		/*time_t*/


class Team;
class Event;

//±»»¸¿‡
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

	void setId(const long & id) {id_ = id;}
	const long & id() {return id_;}	
	void setDate(const time_t & date) { date_ = date;}
	const time_t & date() {return date_;}
	void setResult(const char & result) {result_ = result;}
	const char & result() {return result_;}
	void setStatus(const MatchStatus & status) {status_ = status;}
	const MatchStatus & status() {return status_;}	
	void setHomeScore(const char & homeScore) {homeScore_ = homeScore;}
	const char & homeScore() {return homeScore_;}	
	void setGuestScore(const char & guestScore) {guestScore_ = guestScore;}
	const char & guestScore() {return guestScore_;}	
	void setHomeScoreHarf(const char & homeScoreHarf) {homeScoreHarf_ = homeScoreHarf;}
	const char & homeScoreHarf() {return homeScoreHarf_;}	
	void setGuestScoreHarf(const char & guestScoreHarf) {guestScoreHarf_ = guestScoreHarf;}
	const char & guestScoreHarf() {guestScoreHarf_;}

	void setHomeTeam(Team* homeTeam) {homeTeam_ = homeTeam;}
	Team* homeTeam() const {return homeTeam_;}
	void setGuestTeam(Team* guestTeam) {guestTeam_ = guestTeam;}
	Team* guestTeam() const {return  guestTeam_;}
	void setEvent(Event* event) {event_ = event;}
	Event* event() const {return event_;}


private:
	long id_;			

	time_t date_;	

	char result_;	
	MatchStatus status_;	

	char homeScore_;
	char guestScore_;	
	char homeScoreHarf_;
	char guestScoreHarf_;	

	Team* homeTeam_;		
	Team* guestTeam_;

	Event* event_;		

};

#endif 	//_MATCH_H__
