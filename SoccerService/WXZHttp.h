#ifndef _HTTP_H__
#define _HTTP_H__
#pragma once

#include <WININET.H>			/*HINTERNET*/
#pragma comment(lib, "Wininet.lib")

using namespace std;


#define HTTP_REQUEST_SUCCESS	0
#define HTTP_REQUEST_FAIL		-1
#define HTTP_INVALID_HANDLE		-2
#define HTTP_INVALID_PARAM		-3

class Http
{
public:
	Http();
	~Http();

	const wstring & path() {return path_;}
	void setPath(const wstring & path){path_= path;}

	const wstring & hostName() {return hostName_;}
	void setHostName(const wstring & hostName){hostName_ = hostName;}

	const int & serverPort() { return serverPort_;}
	void setServerPort(const int & serverPort) { serverPort_ = serverPort;}

	bool isInit() {return init_;}


 	int doGet(wstring & request, wstring & responseBuf, bool isHtml=false);
// 	int doPost(const string & postUrl, const string & data, string & responseBuf);	

	void init();
	void uninit();

protected:
//	int doRequest(const char * ip, MStringBuffer & request, MStringBuffer & responseBuf);


private:
	wstring path_;			//服务器URL路径
	wstring hostName_;		//服务器域名

	int serverPort_;		//服务器端口

	string response_;		//返回字符串

	bool init_;

	HINTERNET hInternet_;
	HINTERNET hConnect_;
	HINTERNET hRequest_;
};



#endif //_HTTP_H__
