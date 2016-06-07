#include "stdafx.h"
#include "ParseFileBfdata.h"
#include <sstream>		/*wstringstream*/
#include "WXZMatch.h"
#include "Util.h"
#include "WXZTeam.h"
#include "WXZEvent.h"

ParseFileBfdata::ParseFileBfdata()
{

}

ParseFileBfdata::~ParseFileBfdata()
{

}


void ParseFileBfdata::parseMatchList(const wstring & matchRecord, vector<Match*>& matchList)
{
	int posStart = 0, posStop = 0, lineNum = 0;
	wstring line = L"";

	int matchCount = 0;
	do 
	{
		posStop = matchRecord.find(L"\n", posStart);
		if (posStop>posStart && posStop>=0)
		{
			line = matchRecord.substr(posStart, posStop-posStart);

			if (lineNum==3)//match count
			{
				matchCount = getMatchCount(line);
			}
			else if (lineNum>=6 && matchCount>0 && lineNum<(matchCount+6))
			{
				//A[0]
				Match* match = getMatch(line);
				matchList.push_back(match);
			}
			else
			{
				//B[0],C[0]

			}
			posStart = posStop+1;
			lineNum++;
		}
	} while (posStop>0);
}



//////////////////////////////////////////////////////////////////////////
int ParseFileBfdata::getMatchCount(const wstring & str)
{
	//var matchcount=239;
	if (str.size()<=0)
		return 0;
	int ret = 0;
	int pos1 = str.find(L"=");
	int pos2 = str.find(L";");
	if (pos1>0 && pos2>pos1)
	{
		wstring s = str.substr(pos1+1, pos2-pos1-1);
		return wcs_to_i(s);
	}
	else
		return 0;
}

Match* ParseFileBfdata::getMatch(const wstring & str)
{
	if (str.size() <= 0)
		return 0;
	int pos1 = str.find(L"=\"");
	int pos2 = str.find(L"\".split");
	if (pos1>0 && pos2>pos1)
	{
		wstring s = str.substr(pos1+2, pos2-pos1-2);
#if 0
		wcout.imbue(locale(""));
		wcout<<L"\n"<<s<<endl;
#endif
		vector<wstring> valList;
		split(s, L"^", valList);

		Match* match = new Match();

		Event* matchEvent = new Event;
		matchEvent->setId(wcs_to_l(valList[45]));//赛事ID
		matchEvent->setName(valList[2]);//赛事名称
		Team* homeTeam = new Team;
		homeTeam->setId(wcs_to_l(valList[37]));//主队ID
		homeTeam->setName(valList[5]);//主队名称
		Team* guestTeam = new Team;
		guestTeam->setId(wcs_to_l(valList[38]));//客队ID
		guestTeam->setName(valList[8]);//客队名称

		match->setId(wcs_to_l(valList[0]));//比赛ID
		match->setHomeTeam(homeTeam);
		match->setGuestTeam(guestTeam);
		match->setEvent(matchEvent);
		match->setDate(getMatchDate(valList[43], valList[36], valList[11]));//年，月日，时分
		match->setHomeScore(wcs_to_b(valList[14]));//主队进球
		match->setGuestScore(wcs_to_b(valList[15]));//客队进球
 		match->setHomeScoreHarf(wcs_to_b(valList[16]));//主队上半进球
 		match->setGuestScoreHarf(wcs_to_b(valList[17]));//客队上半进球
		match->setStatus(wcs_to_i(valList[13]));//比赛状态
		if (match->status() == -1)
		{
			if (match->homeScore() > match->guestScore())
				match->setResult(3);
			else if (match->homeScore() < match->guestScore())
				match->setResult(0);
			else
				match->setResult(1);
		}

		return match;
	}
	else
		return 0;
}

time_t ParseFileBfdata::getMatchDate(const wstring & year, const wstring & monthDay, const wstring & hourMinute)
{
	if (year.size()<4 || monthDay.size()<3 || hourMinute.size()<3)
		return 0;
	wstring time_wstring = year+L"-"+monthDay+L" "+hourMinute+L":00";
	return convert_string_to_time_t(wcs_to_mbs(time_wstring, std::locale("")));
}


