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


void ParseFileBfdata::parseMatchList(const wstring matchRecord, vector<Match*>& matchList)
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
				if (lineNum == matchCount+4)
				{
					int m=0;
				}
				Match* match = getMatch(line);
				matchList.push_back(match);
			}
			posStart = posStop+1;
			lineNum++;
		}
	} while (posStop>0);
}



//////////////////////////////////////////////////////////////////////////
int ParseFileBfdata::getMatchCount(wstring str)
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
		return wbs_to_i(s);
	}
	else
		return 0;
}

Match* ParseFileBfdata::getMatch(wstring str)
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
		matchEvent->setId(wbs_to_l(valList[45]));
		matchEvent->setName(valList[2]);
		Team* homeTeam = new Team;
		homeTeam->setId(wbs_to_l(valList[37]));
		homeTeam->setName(valList[5]);
		Team* guestTeam = new Team;
		guestTeam->setId(wbs_to_l(valList[38]));
		guestTeam->setName(valList[8]);

		match->setId(wbs_to_l(valList[0]));
		match->setHomeTeam(homeTeam);
		match->setGuestTeam(guestTeam);
		match->setEvent(matchEvent);

		return match;
	}
	else
		return 0;
}
