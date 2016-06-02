#include "StdAfx.h"
#include "WXZMatch.h"
#include "WXZTeam.h"
#include "WXZEvent.h"

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
}

Match::~Match()
{
	if (homeTeam_)
		delete homeTeam_;
	if (guestTeam_)
		delete guestTeam_;
	if (event_)
		delete event_;
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




