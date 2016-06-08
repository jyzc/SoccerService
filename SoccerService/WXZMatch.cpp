#include "StdAfx.h"
#include "WXZMatch.h"
#include "WXZTeam.h"
#include "WXZEvent.h"



//////////////////////////////////////////////////////////////////////////
// MatchParameter::MatchParameter()
// {
// 	parameterJ_ = 0;
// 	parameterF_ = 0.0;
// 	parameterK_ = 0.0;
// 	parameterH_ = 0.0;
// 	parameterD_ = 0.0;
// 	parameterT_ = 0.0;
// 	fullData_ = 0.0;
// 
// 	z1_=0;
// 	z2_=0;
// 	g1_=0;
// 	g2_=0;
// }
// MatchParameter::~MatchParameter()
// {
// 
// }
// 
// MatchParameter::MatchParameter(const MatchParameter & rhs)
// {
// 
// }
//////////////////////////////////////////////////////////////////////////
Match::Match()
{
	id_ = 0;
	date_ = 0;
	result_ = 0;
	status_= 0;
	homeScore_ = 0;
	guestScore_ = 0;
	homeScoreHarf_ = 0;
	guestScoreHarf_ = 0;

	homeTeam_ = 0;
	guestTeam_ = 0;
	event_ = 0;
	matchParameter_ = 0;
// 	matchParameter_ = new MatchParameter();
}

Match::Match(const Match & rhs)
{
	id_ = rhs.id_;
	date_ = rhs.date_;
	result_ = rhs.result_;
	status_ = rhs.status_;
	homeScore_ = rhs.homeScore_;
	guestScore_ = rhs.guestScore_;
	homeScoreHarf_ = rhs.homeScoreHarf_;
	guestScoreHarf_ = rhs.guestScoreHarf_;

	homeTeam_ = new Team(*rhs.homeTeam_);
	guestTeam_ = new Team(*rhs.guestTeam_);
	event_ = new Event(*rhs.event_);
//  	matchParameter_ = new MatchParameter(*rhs.matchParameter_);
}

Match::~Match()
{
	if (homeTeam_)
		delete homeTeam_;
	if (guestTeam_)
		delete guestTeam_;
	if (event_)
		delete event_;
	if (matchParameter_)
		delete matchParameter_;
}

//////////////////////////////////////////////////////////////////////////
void Match::setJiaoFengRecord(vector<Match*> & jiaoFengRecord)
{
	for (int i=0; i<(int)jiaoFengRecord_.size(); i++)
	{
		delete jiaoFengRecord_[i];
	}
	jiaoFengRecord_.clear();

	jiaoFengRecord_ = jiaoFengRecord;
}


void Match::setJiaoFengRecordSame(vector<Match*> & jiaoFengRecordSame)
{
	for (int i=0; i<(int)jiaoFengRecordSame_.size(); i++)
	{
		delete jiaoFengRecordSame_[i];
	}
	jiaoFengRecordSame_.clear();

	jiaoFengRecordSame_ = jiaoFengRecordSame;
}

void Match::setHomeRecord(vector<Match*> & homeRecord)
{
	for (int i=0; i<(int)homeRecord_.size(); i++)
	{
		delete homeRecord_[i];
	}
	homeRecord_.clear();

	homeRecord_ = homeRecord;
}

void Match::setHomeRecordSame(vector<Match*> & homeRecordSame)
{
	for (int i=0; i<(int)homeRecordSame_.size(); i++)
	{
		delete homeRecordSame_[i];
	}
	homeRecordSame_.clear();

	homeRecordSame_ = homeRecordSame;
}


void Match::setGuestRecord(vector<Match*> & guestRecord)
{
	for (int i=0; i<(int)guestRecord_.size(); i++)
	{
		delete guestRecord_[i];
	}
	guestRecord_.clear();

	guestRecord_ = guestRecord;
}

void Match::setGuestRecordSame(vector<Match*> & guestRecordSame)
{
	for (int i=0; i<(int)guestRecordSame_.size(); i++)
	{
		delete guestRecordSame_[i];
	}
	guestRecordSame_.clear();

	guestRecordSame_ = guestRecordSame;
}




