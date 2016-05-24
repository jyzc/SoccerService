#include "StdAfx.h"
#include "Util.h"
#include <sstream>		/*wstringstream*/


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

#include <locale>
#include <codecvt>
#include <iostream>
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
// 	if (! ss.good())
// 		return L"";
	return s;
}
std::string l_to_mbs(long val)
{
	std::stringstream ss;
	string s;
	ss<<val;
	ss>>s;
// 	if (! ss.good())
// 		return "";
	return s;
}



std::string Utf8ToAnsi(string & utf8)
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