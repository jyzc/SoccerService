#include "StdAfx.h"
#include "WXZMatch.h"


//////////////////////////////////////////////////////////////////////////
Match::Match()
{
	id_ = 0;
	date_ = 0;
	result_ = 0;
	status_= IDLE;
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

}

//////////////////////////////////////////////////////////////////////////
