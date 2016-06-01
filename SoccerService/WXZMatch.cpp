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
