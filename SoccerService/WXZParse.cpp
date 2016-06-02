#include "StdAfx.h"
#include "WXZParse.h"
#include "WXZMatch.h"

#include "ParseFileBfdata.h"
#include "ParseFileAnalysis.h"

Parse::Parse()
{

}


Parse::~Parse()
{

}

//////////////////////////////////////////////////////////////////////////
void Parse::parseMatchList(const wstring matchRecord, vector<Match*>& matchList)
{
	if (matchRecord==L"")
		return;
	for (int i=0; i<(int)matchList.size(); i++)
	{
		delete matchList[i];
	}
	matchList.clear();

	ParseFileBfdata parseFileBfdata;
	parseFileBfdata.parseMatchList(matchRecord, matchList);
}

void Parse::parseMatchRecord(const wstring matchRecord, Match* matchList)
{
	if (matchRecord==L"" || matchList==0)
		return;

	ParseFileAnalysis parseFileAnalysis;
	parseFileAnalysis.parseMatchRecord(matchRecord, matchList);
}
