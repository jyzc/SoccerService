#include "StdAfx.h"
#include "Global.h"
// #include <unistd.h>		/* usleep */

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
		return;
	}

}

void Global::uninit()
{
	Global & g = instance();
	if (!g.init_) 
		return;


}

//////////////////////////////////////////////////////////
void* Global::scanTodayThreadStatic(void*  arg)
{
	((Global *)arg)->scanTodayThread();
	return 0;
}

void  Global::scanTodayThread()
{
	while (scanTodayThreadTerminate_)
	{

		Sleep(1000);
	}//end while (scanTodayThreadTerminate_)	
}



//////////////////////////////////////////////////////////


