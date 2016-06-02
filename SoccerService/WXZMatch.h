#ifndef _MATCH_H__
#define _MATCH_H__
#pragma once

#include <time.h>		/*time_t*/
#include <vector>
using namespace std;

class Team;
class Event;

//������
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
	long id_;				//����ID
	time_t date_;			//����ʱ��
	BYTE result_;			//������� -14�Ƴ�,-12��ն,-11,-10;-1���; 0δ����; 1�ϰ볡;2�г�;3�°볡;
	int status_;	//����״̬	
	BYTE homeScore_;		//���ӽ���
	BYTE guestScore_;		//�Ͷӽ���
	BYTE homeScoreHarf_;	//�����ϰ����
	BYTE guestScoreHarf_;	//�Ͷ��ϰ����

	Team* homeTeam_;		//����
	Team* guestTeam_;		//�Ͷ�
	Event* event_;			//����

	vector<Match*> jiaoFengRecord_;			//�����¼
	vector<Match*> jiaoFengRecordSame_;		//������ͬ�����¼
	vector<Match*> homeRecord_;				//���Ӽ�¼
	vector<Match*> homeRecordSame_;			//����������¼
	vector<Match*> guestRecord_;			//�ͶӼ�¼
	vector<Match*> guestRecordSame_;		//�Ͷӿͳ���¼
};

#endif 	//_MATCH_H__
