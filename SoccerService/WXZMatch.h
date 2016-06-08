#ifndef _MATCH_H__
#define _MATCH_H__
#pragma once

#include <time.h>		/*time_t*/
#include <vector>
using namespace std;

class Team;
class Event;

//���˱��
class MatchFilter
{
public:
	MatchFilter(){};
	~MatchFilter(){};

private:
};

//�㷨����
class MatchParameter
{
public:
	MatchParameter()
	{
		parameterJ_ = 0;
		parameterF_ = 0.0;
		parameterK_ = 0.0;
		parameterH_ = 0.0;
		parameterD_ = 0.0;
		parameterT_ = 0.0;
		fullData_ = 0.0;

		z1_=0;
		z2_=0;
		g1_=0;
		g2_=0;
	};
// 	MatchParameter(const MatchParameter & rhs);
	~MatchParameter(){};

	const int & parameterJ() {return parameterJ_;}
	void setParameterJ(const int & parameterJ){parameterJ_ = parameterJ;}
	const double & parameterF() {return parameterF_;}
	void setParameterF(const double & parameterF){parameterF_ = parameterF;}
	const double & parameterK() {return parameterK_;}
	void setParameterK(const double & parameterK){parameterK_ = parameterK;}
	const double & parameterH() {return parameterH_;}
	void setParameterH(const double & parameterH){parameterH_ = parameterH;}
	const double & parameterD() {return parameterD_;}
	void setParameterD(const double & parameterD){parameterD_ = parameterD;}
	const double & parameterT() {return parameterF_;}
	void setParameterT(const double & parameterT){parameterT_ = parameterT;}
	const double & fullData() {return fullData_;}
	void setFullData(const double & fullData){fullData_ = fullData;}

	const double & z1() {return z1_;}
	void setZ1(const double & z1){z1_ = z1;}
	const double & z2() {return z2_;}
	void setZ2(const double & z2){z2_ = z2;}
	const double & g1() {return g1_;}
	void setG1(const double & g1){g1_ = g1;}
	const double & g2() {return g2_;}
	void setG2(const double & g2){g2_ = g2;}


private:
	int parameterJ_;
	double parameterF_;
	double parameterK_;
	double parameterH_;
	double parameterD_;
	double parameterT_;
	double fullData_;

	double z1_,z2_,g1_,g2_;
};

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
	Match(const Match & rhs);
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
	const BYTE & guestScoreHarf() {return guestScoreHarf_;}

	void setHomeTeam(Team* homeTeam) {homeTeam_ = homeTeam;}
	Team* homeTeam() const {return homeTeam_;}
	void setGuestTeam(Team* guestTeam) {guestTeam_ = guestTeam;}
	Team* guestTeam() const {return  guestTeam_;}
	void setEvent(Event* event) {event_ = event;}
	Event* event() const {return event_;}

	MatchParameter* matchParameter() const { return matchParameter_;}
	void setMatchParameter(MatchParameter* matchParameter) {matchParameter_ = matchParameter;}


	void setJiaoFengRecord(vector<Match*> & jiaoFengRecord);
	vector<Match*> & jiaoFengRecord(){return jiaoFengRecord_;}
	void setJiaoFengRecordSame(vector<Match*> & jiaoFengRecordSame);
	vector<Match*> & jiaoFengRecordSame(){return jiaoFengRecordSame_;}

	void setHomeRecord(vector<Match*> & homeRecord);
	vector<Match*> & homeRecord(){return homeRecord_;}
	void setHomeRecordSame(vector<Match*> & homeRecordSame);
	vector<Match*> & homeRecordSame(){return homeRecordSame_;}
	void setGuestRecord(vector<Match*> & guestRecord);
	vector<Match*> & guestRecord(){return guestRecord_;}
	void setGuestRecordSame(vector<Match*> & guestRecordSame);
	vector<Match*> & guestRecordSame(){return guestRecordSame_;}

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
	MatchParameter* matchParameter_;//�㷨����

	vector<Match*> jiaoFengRecord_;			//�����¼
	vector<Match*> jiaoFengRecordSame_;		//������ͬ�����¼
	vector<Match*> homeRecord_;				//���Ӽ�¼
	vector<Match*> homeRecordSame_;			//����������¼
	vector<Match*> guestRecord_;			//�ͶӼ�¼
	vector<Match*> guestRecordSame_;		//�Ͷӿͳ���¼
};

#endif 	//_MATCH_H__
