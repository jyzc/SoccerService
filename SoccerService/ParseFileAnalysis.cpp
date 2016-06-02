#include "stdafx.h"
#include "ParseFileAnalysis.h"
#include "WXZMatch.h"
#include "WXZTeam.h"
#include "Util.h"

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
	}

}

//////////////////////////////////////////////////////////////////////////
Match* ParseFileAnalysis::getRecord(const wstring matchRecord)
{
	/*
	'15-08-29',//0-����
	25,//����ID
	'��',
	'#009900',
	203,//4-����ID
	'<span title="������11">��ʤ����</span>',//5-��������
	3164,//6-�Ͷ�ID
	'<span title="������12">����ɳ��</span>',
	7,
	1,
	'2-1',
	'ƽ/��',
	-1,
	-1,
	1,
	1096786,
	'8',
	'10'],
	*/
	if (matchRecord.size()<=0)
		return 0;

	int posStart=0, posStop=0;
	wstring line = L"";

	posStart = matchRecord.find(L"[", posStart);
	posStop = matchRecord.find(L"]", posStart);
	if (posStop>=0 && posStop>posStart)
	{
		line = matchRecord.substr(posStart+1, posStop-posStart-1);
#if 1
		wcout.imbue(locale(""));
		wcout<<L"\n"<<line<<endl;
#endif

		vector<wstring> valList;
		split(line, L",", valList);

		Match* match = new Match();

		return match;
	}
	return 0;
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


