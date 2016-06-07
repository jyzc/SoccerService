#ifndef _UTIL_H__
#define _UTIL_H__
#pragma once
#include <vector>

//wstringתstring
std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc);
//stringתwstring
std::wstring mbs_to_wcs(std::string const& str, std::locale loc);
//utf8תwstring
std::wstring utf8_to_wcs(const string & str, std::locale loc);

//longתwstring
std::wstring l_to_wcs(long val);
//longתstring
std::string l_to_mbs(long val);
//wstringתlong
long wcs_to_l(std::wstring val);
//stringתlong
long mbs_to_l(std::string val);


//wstringתint
int wcs_to_i(std::wstring val);
//wtringתBYTE
BYTE wcs_to_b(std::wstring val);


std::string utf8_to_ansi(string & utf8);
std::wstring MBytesToWString(const char* lpcszString);

int split(const wstring json, const wstring ch, vector<wstring>& retList);

time_t convert_string_to_time_t(const std::string & time_string);  
wstring removeChar(wstring & removeStr, wchar_t ch);

#endif	//_UTIL_H__
