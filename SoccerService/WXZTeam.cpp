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
	jiFen_ =  0;		//当前积分
	paiHang_ = 0;	//当前排行
	finishNum_ = 0;	//已赛场次
	shengNum_ = 0;	//胜场次
	fuNum_ = 0;		//负场次
	pingNum_ = 0;	//平场次
	jinQiu_ = 0;	//进球
	shiQiu_ = 0;	//失球

	ttNow_ = 0;
}

LeagueData::~LeagueData()
{

}


