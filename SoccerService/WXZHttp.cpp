#include "StdAfx.h"
#include "WXZHttp.h"

#include "Util.h"

////////////////////////////////////////////////////////////////////////

Http::Http()
{
	path_ = L"";
	response_ = "";
	serverPort_ = 80;
	hostName_ = L"";

	hInternet_ = 0;
	hConnect_ = 0;
	hRequest_ = 0;
	init_ = false;
}

Http::~Http()
{

}

//////////////////////////////////////////////////////////////////////////
int Http::doGet(wstring & request, wstring & responseBuf, bool isHtml)
{
	if (hostName_ == L"" || request == L"" || !init_)
		return HTTP_INVALID_PARAM;

	response_.clear();
	responseBuf.clear();
	if (hRequest_) InternetCloseHandle(hRequest_);
	if (hConnect_) InternetCloseHandle(hConnect_);

	hConnect_ = InternetConnect(hInternet_, hostName_.c_str(), serverPort_, NULL, L"HTTP/1.1", INTERNET_SERVICE_HTTP, 0, 0);
	if (!hConnect_)
	{
		return HTTP_INVALID_HANDLE;
	}

	hRequest_ = HttpOpenRequest(hConnect_, _T("GET"), path_.c_str(), _T("HTTP/1.1"), _T(""), 0, INTERNET_FLAG_RELOAD, 0);
	if (!hRequest_)
	{
		if (hConnect_) InternetCloseHandle(hConnect_);
		return HTTP_INVALID_HANDLE;
	}

	BOOL bRet = HttpSendRequest(hRequest_, request.c_str(), request.length(),_T(""), 0);
	if (!bRet)
	{
		if (hRequest_) InternetCloseHandle(hRequest_);
		if (hConnect_) InternetCloseHandle(hConnect_);
		return HTTP_REQUEST_FAIL;
	}

	while(true)
	{
		char cReadBuffer[4096] = {0};
		unsigned long lNumberOfBytesRead = 0;
		bRet = InternetReadFile(hRequest_, cReadBuffer, sizeof(cReadBuffer) - 1, &lNumberOfBytesRead);
		if(!bRet || !lNumberOfBytesRead)
			break;
		cReadBuffer[lNumberOfBytesRead] = 0;

		response_.append(cReadBuffer);
	}

	if (hRequest_) InternetCloseHandle(hRequest_);
	if (hConnect_) InternetCloseHandle(hConnect_);

	if (isHtml)
	{
		responseBuf = utf8_to_wcs(response_, std::locale(""));
	}
	else
		responseBuf = mbs_to_wcs(response_, std::locale(""));

	return HTTP_REQUEST_SUCCESS;
}

void Http::init()
{
	if (init_) return;

	if (hRequest_) InternetCloseHandle(hRequest_);
	if (hConnect_) InternetCloseHandle(hConnect_);
	if (hInternet_) InternetCloseHandle(hInternet_);

	hInternet_ = InternetOpen(L"User-Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet_)
		return ;
	init_ = true;
}

void Http::uninit()
{
	if (!init_) return;

	if (hRequest_) InternetCloseHandle(hRequest_);
	if (hConnect_) InternetCloseHandle(hConnect_);
	if (hInternet_) InternetCloseHandle(hInternet_);

	init_ = false;
}







