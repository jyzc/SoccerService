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
	jiFen_ =  0;		//��ǰ����
	paiHang_ = 0;	//��ǰ����
	finishNum_ = 0;	//��������
	shengNum_ = 0;	//ʤ����
	fuNum_ = 0;		//������
	pingNum_ = 0;	//ƽ����
	jinQiu_ = 0;	//����
	shiQiu_ = 0;	//ʧ��

	ttNow_ = 0;
}

LeagueData::~LeagueData()
{

}


