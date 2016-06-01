#include "StdAfx.h"
#include "WXZTeam.h"

//////////////////////////////////////////////////////////////////////////
Team::Team()
{
	id_ = 0;
	name_ = L"";
	leagueData_ = 0;
}

Team::~Team()
{
	if (leagueData_)
		delete leagueData_;

}

//////////////////////////////////////////////////////////////////////////

LeagueData::LeagueData()
{
}

LeagueData::~LeagueData()
{

}


