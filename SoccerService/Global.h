#ifndef _GLOBAL_H__
#define _GLOBAL_H__
#pragma once

#include <pthread.h>		/* thread */

using namespace std;

class Global
{
public:

	static Global & instance()
	{
		static Global global;
		return global;		
	}

	static void init();
	static void uninit();


private:
	Global();
	~Global();

	bool init_;			//初始化标记

	//扫描今天比赛列表线程
	pthread_t sacnTodayThread_;		//线程接口
	static void* scanTodayThreadStatic(void* arg);
	void scanTodayThread();			//线程实体
	bool scanTodayThreadTerminate_;	//线程结束标记
	void resetScanTodayThread();	//复位线程

	//扫描历史比赛列表线程
	pthread_t sacnOverThread_;
	static void* scanOverThreadStatic(void* arg);
	void scanOverThread();
	bool scanOverThreadTerminate_;
	void resetScanOverThread();

	pthread_mutex_t dbMutex_;		//数据库操作互斥体

};

#endif	//_GLOBAL_H__

