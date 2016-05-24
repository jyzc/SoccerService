// SoccerService.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>			/* cout */

#include "WXZHttp.h"
#include <time.h>			/*time_t*/
#include "Util.h"

//////////////////////////////////////////////////////////////////////////

void MainProcess();
void DrawHeader();

//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	MainProcess();
	return 0;
}

void MainProcess()
{
	DrawHeader();

	time_t tt;
	time(&tt);  

	Http http;
	http.init();
	//1
	http.setHostName(L"live3.win007.com");
	wstring s=L"/vbsxml/bfdata.js?r=007"+l_to_wcs(tt)+L"000";	
	http.setPath(s);

	wstring request,response;


//	request.append(L"GET ").append(L"/vbsxml/bfdata.js?r=007").append(l_to_wcs(tt)).append(L"000").append(L" HTTP/1.1\r\n");
//	request.append(L"Accept: */*").append(L"\r\n");
//	header.append("User-Agent: ").append("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:46.0) Gecko/20100101 Firefox/46.0\r\n");
//	request.append(L"Content-Type: application/javascript\r\n");
//	request.append(L"Host: ").append(L"live3.win007.com").append(L"\r\n");
// 	request.append(L"\r\n");

	request.append(L"Referer: http://live3.win007.com/\r\n");
	request.append(L"Connection: keep-alive\r\n");

	if (http.isInit())
		http.doGet(request, response);

	wcout.imbue(locale(""));
	wcout<<L"\n\n\n"<<response<<endl;


	//2
	if (!http.isInit()) http.init();
	http.setHostName(L"zq.win007.com");
	http.setPath(L"/analysis/1132220sb.htm");

	request.clear();
	response.clear();

	request.append(L"Referer: http://bf.win007.com/\r\n");
	request.append(L"Connection: keep-alive\r\n");

	http.doGet(request, response, true);

	wcout.imbue(locale(""));
	wcout<<L"\n\n\n"<<response<<endl;

	http.uninit();
}

void DrawHeader()
{
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++\n"
		<<"+         MatchServer V1.0                     +\n"
		<<"+                                              +\n"
		<<"+         Release date:2016-5-10               +\n"
		<<"++++++++++++++++++++++++++++++++++++++++++++++++\n"<<endl;	
}

