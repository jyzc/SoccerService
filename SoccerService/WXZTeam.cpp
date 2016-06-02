#include "StdAfx.h"
#include "WXZTeam.h"

//////////////////////////////////////////////////////////////////////////
Team::Team()
{
	id_ = 0;
	name_ = L"";
	leagueData_ = 0;
}

Team::Team(const Team & rhs)
{
	id_ = rhs.id_;
	name_ = rhs.name_;
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


