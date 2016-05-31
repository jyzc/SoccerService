#ifndef _UTIL_H__
#define _UTIL_H__
#pragma once
#include <vector>

std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc);
std::wstring mbs_to_wcs(std::string const& str, std::locale loc);

std::wstring utf8_to_wcs(const string & str, std::locale loc);


std::wstring l_to_wcs(long val);
std::string l_to_mbs(long val);
long wbs_to_l(std::wstring val);
int wbs_to_i(std::wstring val);

std::string Utf8ToAnsi(string & utf8);
std::wstring MBytesToWString(const char* lpcszString);

int split(const wstring json, const wstring ch, vector<wstring>& retList);

#endif	//_UTIL_H__
