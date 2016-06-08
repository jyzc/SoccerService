#include "stdafx.h"
#include "WXZNetRequest.h"
#include "WXZHttp.h"
#include <time.h>			/*time()*/
#include "Util.h"			/*l_to_wcs*/
#include "WXZParse.h"
#include "WXZMatch.h"

NetRequest::NetRequest()
{
	http_ = new Http();
}

NetRequest::~NetRequest()
{
	if (http_)
	{
		http_->uninit();
		delete http_;
	}
}

//获得比赛基本信息matchList
void NetRequest::getMatchList(vector<Match*>& matchList)
{
	if (http_ == 0) 
		return;
	if (!http_->isInit())
		http_->init();

	time_t tt;
	time(&tt);  
	http_->setHostName(L"live3.win007.com");
	wstring s=L"/vbsxml/bfdata.js?r=007"+l_to_wcs((long)tt)+L"000";	
	http_->setPath(s);

	wstring request,response;
	request.append(L"Referer: http://live3.win007.com/\r\n");
	request.append(L"Connection: keep-alive\r\n");

	http_->doGet(request, response);
#if 0
	wcout.imbue(locale(""));
	wcout<<L"\n"<<response<<endl;
#endif

	Parse parse;
	parse.parseMatchList(response, matchList);
}

//获得比赛对战数据
bool NetRequest::getMatchData(Match* matchList)
{
	if (!http_->isInit())
		http_->init();

	http_->setHostName(L"zq.win007.com");
	wstring s=L"/analysis/"+l_to_wcs(matchList->id())+L"sb.htm";	
	http_->setPath(s);

	wstring request,response;
	request.append(L"Referer: http://live3.win007.com/\r\n");
	request.append(L"Connection: keep-alive\r\n");

	http_->doGet(request, response, true);
#if 0
	wcout.imbue(locale(""));
	wcout<<L"\n"<<response<<endl;
#endif

	Parse parse;
 	parse.parseMatchRecord(response, matchList);
	return true;
}