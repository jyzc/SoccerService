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

	bool init_;			//��ʼ�����

	//ɨ���������б��߳�
	pthread_t sacnTodayThread_;		//�߳̽ӿ�
	static void* scanTodayThreadStatic(void* arg);
	void scanTodayThread();			//�߳�ʵ��
	bool scanTodayThreadTerminate_;	//�߳̽������
	void resetScanTodayThread();	//��λ�߳�

	//ɨ����ʷ�����б��߳�
	pthread_t sacnOverThread_;
	static void* scanOverThreadStatic(void* arg);
	void scanOverThread();
	bool scanOverThreadTerminate_;
	void resetScanOverThread();

	pthread_mutex_t dbMutex_;		//���ݿ����������

};

#endif	//_GLOBAL_H__

