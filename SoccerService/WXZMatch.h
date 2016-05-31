#ifndef _MATCH_H__
#define _MATCH_H__
#pragma once

#include <time.h>		/*time_t*/


class Team;
class Event;

//������
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
	long id_;				//����ID
	time_t date_;			//����ʱ��
	BYTE result_;			//������� 0��1��3
	MatchStatus status_;	//����״̬	
	BYTE homeScore_;		//���ӽ���
	BYTE guestScore_;		//�Ͷӽ���
	BYTE homeScoreHarf_;	//�����ϰ����
	BYTE guestScoreHarf_;	//�Ͷ��ϰ����

	Team* homeTeam_;		//����
	Team* guestTeam_;		//�Ͷ�
	Event* event_;			//����

};

#endif 	//_MATCH_H__
