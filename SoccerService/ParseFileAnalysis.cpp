#include "stdafx.h"
#include "ParseFileAnalysis.h"
#include "WXZMatch.h"
#include "WXZTeam.h"
#include "Util.h"
#include "WXZEvent.h"

ParseFileAnalysis::ParseFileAnalysis()
{

}
ParseFileAnalysis::~ParseFileAnalysis()
{

}

void ParseFileAnalysis::parseMatchRecord(const wstring matchRecord, Match* matchList)
{
	int posStart=0, posStop=0;
	wstring line = L"";

	vector<Match*> jiaoFeng,jiaoFengSame, homeRecord, homeRecordSame, guestRecord, guestRecordSame;
	// ����
	posStart = matchRecord.find(L"v_data=[", posStart);
	posStop = matchRecord.find(L"];", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart+8, posStop-posStart-8);
		getJiaoFengRecord(line, jiaoFeng, jiaoFengSame, matchList->homeTeam()->id(), matchList->guestTeam()->id());
		posStart = posStop;
	}

	//����
	posStart = matchRecord.find(L"h_data=[", posStart);
	posStop = matchRecord.find(L"];", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart+8, posStop-posStart-8);
		getRecords(line, homeRecord);
		posStart = posStop;
	}

	//�Ͷ�
	posStart = matchRecord.find(L"a_data=[", posStart);
	posStop = matchRecord.find(L"];", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart+8, posStop-posStart-8);
		getRecords(line, homeRecord);
		posStart = posStop;
	}

	//��������
	posStart = matchRecord.find(L"h2_data=[", posStart);
	posStop = matchRecord.find(L"];", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart+9, posStop-posStart-9);
		getRecords(line, homeRecordSame);
		posStart = posStop;
	}


	//�Ͷӿͳ�
	posStart = matchRecord.find(L"a2_data=[", posStart);
	posStop = matchRecord.find(L"];", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart+9, posStop-posStart-9);
		getRecords(line, homeRecordSame);
		posStart = posStop;
	}

	//����������������
	posStart = matchRecord.find(L"\"porletP_Group\"", posStart);
	if (posStart<0)
		return;	
	posStart = matchRecord.find(L"\"porlet_5\"", posStart);
	if (posStart<0)
		return;	
	posStart = matchRecord.find(L"ȫ��", posStart);
	if (posStart<0)
		return;
	posStart = matchRecord.find(L"<tr", posStart);
	posStop = matchRecord.find(L"</tr>", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart, posStop-posStart+5);

		posStart = posStop;
	}

}

//////////////////////////////////////////////////////////////////////////
Match* ParseFileAnalysis::getRecord(const wstring matchRecord)
{
	/*
	'15-08-29',//0-����
	25,//1-����ID
	'��',
	'#009900',
	203,//4-����ID
	'<span title="������11">��ʤ����</span>',//5-��������
	3164,//6-�Ͷ�ID
	'<span title="������12">����ɳ��</span>',//7
	7,//8-���ӽ���
	1,//9-�Ͷӽ���
	'2-1',//10-�볡�ȷ�
	'ƽ/��',//11
	-1,//12
	-1,//13
	1,//14
	1096786,//15-����ID
	'8',//16
	'10'],//17
	*/
	if (matchRecord.size()<=0)
		return 0;

	int posStart=0, posStop=0;
	if (matchRecord[0] == L'[')
		posStart = 1;

	wstring line = L"";
	int len = matchRecord.size();
	if (matchRecord[len-1] == L']')
		posStop = len-2;
	else
		posStop = len-1;
	line = matchRecord.substr(posStart, posStop-posStart+1);

#if 1
	wcout.imbue(locale(""));
	wcout<<L"\n"<<line<<endl;
#endif

	vector<wstring> valList;
	split(line, L",", valList);

	Match* match = new Match();
	match->setId(wcs_to_l(valList[15]));
	match->setDate(getTime(removeChar(valList[0], L'\'')));
	match->setHomeScore(wcs_to_b(valList[8]));
	match->setGuestScore(wcs_to_b(valList[9]));
	BYTE homeHarf=0, guestHarf=0;
	getHarfScore(removeChar(valList[10], L'\''), homeHarf, guestHarf);
	match->setHomeScoreHarf(homeHarf);
	match->setGuestScoreHarf(guestHarf);

	Event* event = new Event();
	event->setId(wcs_to_l(valList[1]));
	event->setName(removeChar(valList[2], L'\''));
	Team* host = new Team();
	host->setId(wcs_to_l(valList[4]));
	host->setName(getName(valList[5]));
	Team* guest = new Team();
	guest->setId(wcs_to_l(valList[6]));
	guest->setName(getName(valList[7]));

	match->setEvent(event);
	match->setHomeTeam(host);
	match->setGuestTeam(guest);
	return match;
}
void ParseFileAnalysis::getRecords(const wstring matchRecord, vector<Match*>& homeRecord)
{
	if (matchRecord.size()<=0)
		return;

	vector<wstring> recordList;
	split(matchRecord, L"],", recordList);

	for (int i=0; i<(int)recordList.size(); i++)
	{
		Match* match = getRecord(recordList[i]);
		homeRecord.push_back(match);
	}
}




void ParseFileAnalysis::getJiaoFengRecord(const wstring matchRecord, vector<Match*>& jiaoFeng, vector<Match*> &jiaoFengSame, long homeId, long guestId)
{
	//['15-08-29',25,'��','#009900',203,'<span title="������11">��ʤ����</span>',3164,'<span title="������12">����ɳ��</span>',7,1,'2-1','ƽ/��',-1,-1,1,1096786,'8','10'],
	if (matchRecord.size()<=0)
		return;
	getRecords(matchRecord, jiaoFeng);
	for (int i=0; i<(int)jiaoFeng.size(); i++)
	{
		Match* match = jiaoFeng[i];
		if (match->homeTeam()->id() == homeId && match->guestTeam()->id() == guestId)
		{
			Match* matchSame = new Match(*match);
			jiaoFengSame.push_back(matchSame);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
time_t ParseFileAnalysis::getTime(const wstring value)
{
	//'15-08-29'
	if (value.size()<=0)
		return 0;
	wstring s = value + L" 00:00:00";
	return convert_string_to_time_t(wcs_to_mbs(s, locale("")));
}

wstring ParseFileAnalysis::getName(const wstring value)
{
	//'<span title="������11">��ʤ����</span>'
	//'<span title="�����������2"><span class=hp>1</span>�W����</span>'
	//'<span title="�����������11">����ģ(��)</span>'
	//'<span title="������15">����ģ<span class=hp>1</span></span>'
	//'<span title="�հ���SP (Ů)  ����:">�հ���S</span><span class=hp>1</span>'

	if (value.size()<=0)
		return L"";

	int posStart=0, posStop=0;
	wstring line = value;
	//ȥ����//<span class=hp>1</span>
	posStart = line.find(L"class=hp");
	if (posStart>=0)
	{
		posStart = line.find_last_of(L"<span", posStart);
		posStart -= 4;
		posStop = line.find(L"</span>", posStart);
		posStop += 7;
		line.erase(posStart, posStop-posStart);
	}

	//ȥ��һ��span
	posStart = line.find(L"<span");
	if (posStart>=0)
	{
		posStop = line.find(L">", posStart);
		posStart = posStop+1;
		posStop = line.find(L"</span>");
	}
	if (posStop>=0 && posStart>=0 && posStop>posStart)
		line = line.substr(posStart, posStop-posStart);

	//ȥ�г�//(��)
	posStart = line.find(L"(");
	if (posStart>=0)
		posStop = line.find(L"��", posStart);
	if (posStop>=0 && posStart>=0 && posStop>posStart)
		line.erase(posStart, 3);
	
	return line;
}

void ParseFileAnalysis::getHarfScore(const wstring value, BYTE& homeScore, BYTE& guestScore)
{
	//'2-1'
	if (value.size()<=0)
		return;
	vector<wstring> valueList;
	split(value, L"-", valueList);
	if (valueList.size()==2)
	{
		homeScore = wcs_to_b(valueList[0]);
		guestScore = wcs_to_b(valueList[1]);
	}
}


// void ParseFileAnalysis::getHomeRecord(const wstring matchRecord, vector<Match*>& homeRecord)
// {
// 
// }
// 
// void ParseFileAnalysis::getGuestRecord(const wstring matchRecord, vector<Match*>& guestRecord)
// {
// 
// }
// 
// void ParseFileAnalysis::getHomeRecordSame(const wstring matchRecord, vector<Match*>& homeRecordSame)
// {
// 
// }
// 
// void ParseFileAnalysis::getGuestRecordSame(const wstring matchRecord, vector<Match*>& guestRecordSame)
// {
// 
// }


