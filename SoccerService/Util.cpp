#include "StdAfx.h"
#include "Util.h"
#include <sstream>		/*wstringstream*/
#include <locale>
#include <codecvt>
#include <iostream>

#pragma warning(disable:4996) 

//////////////////////////////////////////////////////////////////////////
char gMatchStatus[5][20] = {"完","中","推迟","待定","腰斩"};

char gYazhi1[20][20] = {"平手","平/半","半球","半/一","一球","一球/球半","球半","球半/两球","两球","两球/两球半","两球半","两球半/三球","三球","三球/三球半","三球半","三球半/四球","四球","四球/四球半","四球半","四球半/五球"};
char gYazhi2[20][20] = {"平手","受平/半","受半球","受半/一","受一球","受一球/球半","受球半","受球半/两球","受两球","受两球/两球半","受两球半","受两球半/三球","受三球","受三球/三球半","受三球半","受三球半/四球","受四球","受四球/四球半","受四球半","受四球半/五球"};
char gYazhi3[20][20] = {"平手","*平/半","*半球","*半/一","*一球","*一球/球半","*球半","*球半/两球","*两球","*两球/两球半","*两球半","*两球半/三球","*三球","*三球/三球半","*三球半","*三球半/四球","*四球","*四球/四球半","*四球半","*四球半/五球"};


//////////////////////////////////////////////////////////////////////////
std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc)
{
	typedef std::codecvt <wchar_t,char,std::mbstate_t> codecvt_t;
	std::codecvt <wchar_t,char,std::mbstate_t> const& codecvt = std::use_facet<codecvt_t>(loc);
	std::mbstate_t state = std::mbstate_t();
	std::vector<char> buf((str.size() + 1) * codecvt.max_length());
	wchar_t const* in_next = str.c_str();
	char* out_next = &buf[0];
	codecvt_t::result r = codecvt.out(state, str.c_str(),str.c_str() + str.size(), in_next, &buf[0], &buf[0] + buf.size(), out_next);
	return std::string(&buf[0]);
}

std::wstring mbs_to_wcs(std::string const& str, std::locale loc)
{
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	std::mbstate_t state = std::mbstate_t();
	std::vector<wchar_t> buf(str.size() + 1);
	char const* in_next = str.c_str();
	wchar_t* out_next = &buf[0];
	std::codecvt_base::result r = codecvt.in(state, 
		str.c_str(), str.c_str() + str.size(), in_next, 
		&buf[0], &buf[0] + buf.size(), out_next);
	if (r == std::codecvt_base::error)
		throw std::runtime_error("can't convert string to wstring");   
	return std::wstring(&buf[0]);
}

std::wstring utf8_to_wcs(const string & str, std::locale loc)
{
	int iLenByWChNeed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.size(), NULL, 0);

	wchar_t* pTemp = new wchar_t[iLenByWChNeed * 2];
	char* pOutBuf = new char[iLenByWChNeed * 2];

	memset(pTemp, 0, iLenByWChNeed * 2*sizeof(wchar_t));
	memset(pOutBuf, 0, iLenByWChNeed * 2*sizeof(char));

	int iLenByWchDone = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pTemp, iLenByWChNeed); 

	//unicode -> asci
	int iLenByChNeed  = WideCharToMultiByte(CP_ACP, 0, pTemp, iLenByWchDone, NULL, 0, NULL, NULL); 
	int iLenByChDone  = WideCharToMultiByte(CP_ACP, 0, pTemp, iLenByWchDone, pOutBuf, iLenByChNeed, NULL, NULL);

	delete pTemp;
	if (iLenByWChNeed != iLenByWchDone || iLenByChNeed != iLenByChDone)
		return L"";

	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	std::mbstate_t state = std::mbstate_t();

	std::vector<wchar_t> buf(str.size() + 1);
 	char const* in_next = pOutBuf;
	wchar_t* out_next = &buf[0];
	std::codecvt_base::result r = codecvt.in(state, pOutBuf, pOutBuf + iLenByChDone, in_next, &buf[0], &buf[0] + buf.size(), out_next);
	delete pOutBuf;
	if (r == std::codecvt_base::error)
		throw std::runtime_error("can't convert string to wstring");   
	return std::wstring(&buf[0]);
}
//////////////////////////////////////////////////////////////////////////
std::wstring l_to_wcs(long val)
{
	std::wstringstream ss;
	wstring s;
	ss<<val;
	ss>>s;
	return s;
}
std::string l_to_mbs(long val)
{
	std::stringstream ss;
	string s;
	ss<<val;
	ss>>s;
	return s;
}

long mbs_to_l(std::string val)
{
	if (val.size()<=0)
		return 0;

	std::stringstream ss;
	long s;
	ss<<val;
	ss>>s;
	return s;
}

long wcs_to_l(std::wstring val)
{
	if (val.size()<=0)
		return 0;

	std::wstringstream ss;
	long s;
	ss<<val;
	ss>>s;
	return s;
}
int wcs_to_i(std::wstring val)
{
	if (val.size()<=0)
		return 0;
	std::wstringstream ss;
	int s;
	ss<<val;
	ss>>s;
	return s;
}
BYTE wcs_to_b(std::wstring val)
{
	if (val.size()<=0)
		return 0;

	std::wstringstream ss;
	unsigned short s;
	ss<<val;
	ss>>s;
	return (BYTE)s;
}



std::string utf8_to_ansi(string & utf8)
{
	if (utf8=="")
		return "";
	int k = utf8.length();

	//utf-8 -> unicode
	int iLenByWChNeed = MultiByteToWideChar(CP_UTF8, 
		0, 
		utf8.c_str(), 
		utf8.length(), //MultiByteToWideChar
		NULL, 0);

	WCHAR* pTemp = new WCHAR[iLenByWChNeed * 2];
	char* pOutBuf = new char[iLenByWChNeed * 2];

	memset(pTemp, 0, iLenByWChNeed * 2*sizeof(WCHAR));
	memset(pOutBuf, 0, iLenByWChNeed * 2*sizeof(char));

	int iLenByWchDone = MultiByteToWideChar(CP_UTF8, 0,
		utf8.c_str(),
		utf8.length(),
		pTemp,
		iLenByWChNeed); //MultiByteToWideChar

	//unicode -> asci
	int iLenByChNeed  = WideCharToMultiByte(CP_ACP, 0,
		pTemp,
		iLenByWchDone,
		NULL, 0,
		NULL, NULL); 

	int iLenByChDone  = WideCharToMultiByte(CP_ACP, 0,
		pTemp,
		iLenByWchDone,
		pOutBuf,
		iLenByChNeed,
		NULL, NULL);
	delete pTemp;
	if (iLenByWChNeed != iLenByWchDone || iLenByChNeed != iLenByChDone)
		return "";
	int k1 = strlen(pOutBuf);
	string s = (char*) pOutBuf;
	delete pOutBuf;
	return s;
}

std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	wstring wString = (wchar_t*)pUnicode;
	delete [] pUnicode;
	return wString;
}


int split(const wstring json, const wstring ch, vector<wstring>& retList)
{
	int cellSize = ch.size();
	retList.clear();

	int posStart=0, posStop=0;
	wstring value = L"";
	do 
	{
		posStop = json.find(ch, posStart);
		if (posStop>=0 && posStop>=posStart)
			value = json.substr(posStart, posStop-posStart);
		else
			value = json.substr(posStart, json.length());
		retList.push_back(value);
		posStart = posStop+cellSize;
	} while (posStop>0);

	return (int)retList.size();
}

time_t convert_string_to_time_t(const std::string & time_string)  
{  
	struct tm tm1;  
	int i = sscanf(time_string.c_str(), "%d-%d-%d %d:%d:%d" ,       
		&(tm1.tm_year),   
		&(tm1.tm_mon),   
		&(tm1.tm_mday),  
		&(tm1.tm_hour),  
		&(tm1.tm_min),  
		&(tm1.tm_sec),  
		&(tm1.tm_wday),  
		&(tm1.tm_yday));  

	tm1.tm_year -= 1900;  
	tm1.tm_mon --;  
	tm1.tm_isdst=-1;  

	return mktime(&tm1);
}  

wstring removeChar(wstring & removeStr, wchar_t ch)
{
	if (removeStr.size()<=0)
		return L"";
	for (int i=0; i<(int)removeStr.size(); i++)
	{
		if (removeStr[i] == ch)
		{
			removeStr.erase(i, 1);
			i--;
		}
	}
	return removeStr;
}