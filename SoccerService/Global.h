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

	bool init_;


	pthread_t sacnTodayThread_;
	static void* scanTodayThreadStatic(void* arg);
	void scanTodayThread();
	bool scanTodayThreadTerminate_;
	void resetScanTodayThread();


	pthread_t sacnOverThread_;
	static void* scanOverThreadStatic(void* arg);
	void scanOverThread();
	bool scanOverThreadTerminate_;
	void resetScanOverThread();

	pthread_mutex_t dbMutex_;

};

#endif	//_GLOBAL_H__

