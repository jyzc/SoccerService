#include "StdAfx.h"
#include "Global.h"
// #include <unistd.h>		/* usleep */
#include <iostream>			/* cout */
#include "WXZNetRequest.h"
#include "WXZDBOperator.h"

#include "..\\MatchAlgorithm\\MatchAlgorithm.h"
#pragma comment(lib, "..\\Debug\\MatchAlgorithm.lib")

//////////////////////////////////////////////////////////////////////////
Match* findMatch(long findId, vector<Match*> todayList)
{	
	for (int i=0; i<(int)todayList.size(); i++)
	{
		if (todayList[i]->id()==findId)
			return todayList[i];
	}
	return 0;
}

void compareList(vector<Match*> & matchList, const vector<Match*> & todayList,  vector<Match*>& updateList)
{
	for (int i=0; i<(int)matchList.size(); i++)
	{
		Match* match = matchList[i];
		Match* matchDB = findMatch(match->id(), todayList);
		if (matchDB)
		{
			if (match->status() != matchDB->status())
			{
				updateList.push_back(match);
				matchList.erase(matchList.begin()+i);
				i--;
			}
		}
		else
		{
			updateList.push_back(match);
			matchList.erase(matchList.begin()+i);
			i--;
		}
	}
}

void releaseVector(vector<Match*> & matchList)
{
	vector<Match*>::iterator iter;
	for (iter=matchList.begin(); iter!=matchList.end(); iter++)
	{
 		delete *iter;
	}
	matchList.clear();
}

//////////////////////////////////////////////////////////////////////////
Global::Global()
{

}

Global::~Global()
{

}

void Global::init()
{
	Global & g = instance();
	if (g.init_)
	{
// 		g.resetLoadThread();
// 		g.resetSaveThread();
		return;
	}

	g.scanTodayThreadTerminate_ = false;	
	g.scanOverThreadTerminate_ = false;	


	pthread_mutex_init(&g.dbMutex_, 0);
	pthread_create(&g.sacnTodayThread_, 0, Global::scanTodayThreadStatic, &g);
	pthread_create(&g.sacnOverThread_, 0, Global::scanOverThreadStatic, &g);
	g.init_ = true;

}

void Global::uninit()
{
	Global & g = instance();
	if (!g.init_) 
		return;


	g.scanTodayThreadTerminate_ = true;
	pthread_join(g.sacnTodayThread_, 0);	
	g.scanOverThreadTerminate_ = true;
	pthread_join(g.sacnOverThread_, 0);	
	pthread_mutex_destroy(&g.dbMutex_);

	g.init_ = false;

}

//////////////////////////////////////////////////////////
void* Global::scanTodayThreadStatic(void*  arg)
{
	((Global *)arg)->scanTodayThread();
	return 0;
}

void  Global::scanTodayThread()
{
	vector<Match*> matchList, todayList, updateList;
	NetRequest netRequest;
	while (!scanTodayThreadTerminate_)
	{
		//请求网络，获得比赛列表matchList
		netRequest.getMatchList(matchList);

		//读取数据库，获得当天比赛列表todayList
		DBOperator dbOperator;
		pthread_mutex_lock(&dbMutex_);
		dbOperator.getTodayList(todayList);
		pthread_mutex_unlock(&dbMutex_);

		//比较获得updateList，
		compareList(matchList, todayList, updateList);
		releaseVector(todayList);
		releaseVector(matchList);

		//请求网页信息
		for (int i=0; i<(int)updateList.size(); i++)
		{
			Match* updateMatch = updateList[i];
			//请求交锋记录
			netRequest.getMatchData(updateMatch);


			//算法,是否封装dll？
			CalculateH(updateMatch);
		}

		//添加数据入库
		pthread_mutex_lock(&dbMutex_);
		dbOperator.updateData(updateList);
		pthread_mutex_unlock(&dbMutex_);

		releaseVector(updateList);
		Sleep(1000);
	}//end while (scanTodayThreadTerminate_)

	releaseVector(matchList);
	releaseVector(todayList);
	releaseVector(updateList);
}

void* Global::scanOverThreadStatic(void* arg)
{
	((Global *)arg)->scanOverThread();
	return 0;
}

void Global::scanOverThread()
{
	int j=0;
	while (!scanOverThreadTerminate_)
	{
		pthread_mutex_lock(&dbMutex_);
		cout<<"[OverThread]:"<<j++<<endl;
		pthread_mutex_unlock(&dbMutex_);

		Sleep(1000);
	}//end while (scanOverThreadTerminate_)
}
//////////////////////////////////////////////////////////


