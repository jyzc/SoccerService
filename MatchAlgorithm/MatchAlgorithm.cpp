// MatchAlgorithm.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MatchAlgorithm.h"

#include "..\\..\\SoccerService\\SoccerService\\WXZMatch.h"
#include "..\\..\\SoccerService\\SoccerService\\WXZTeam.h"


//////////////////////////////////////////////////////////////////////////
void CalculateH(Match* match)
{
	/************************************************************************/
	/*  1、基本面     n1+n2+n3+n4+n5+n6+n7+n8+n9+n10                        */
	/*   n1：当前联赛基本差                                                 */
	/*   n2：最近6场交锋胜负差                                              */
	/*   n3：最近6场相同交锋胜负差                                          */
	/*   n4：最近6场积分差                                                  */
	/*   n5：最近6场本队进球数差                                            */
	/*   n6：最近6场主客场积分差                                            */
	/*   n7：最近6场主客场进球数差                                          */
	/*   n8：最近一场交锋胜负差                                             */
	/*   n9：最近一场胜负差                                                 */
	/*   n10：最近一场本队进球数差                                          */
	/*                                                                      */
	/*  2、大小球 (a+b+c)/3                                                 */
	/*  a：双方最近交锋6场得失球数/6+双方最近交锋3场得失球数/3）/2          */
	/*  b：双方最近6场比赛得失球数/12                                       */
	/*  c：双方最近3场比赛得失球数/6                                        */
	/*                                                                      */
	/*  3、大球率   (da+db+dc)/3                                            */
	/*  da：双方最近交锋6场大球场次数/6+双方最近交锋3场大球场次数/3）/2     */
	/*  db：双方最近6场比赛大球场次数/12                                    */
	/*  dc：双方最近3场比赛大球场次数/6                                     */
	/*																		*/
	/*	4.进球率 ()															*/
	/*	Win1	主队最近10场进球数										    */
	/*	Lose1	主队最近10场失球数											*/
	/*	Win2	客队最近10场进球数											*/
	/*	Lose2	客队最近10场失球数											*/
	/*	Dxl1																*/
	/*	Dql2																*/
	/*																		*/
	/*  5.F=F1*40%+F2*40%+F3*20%											*/
	/*  F1=最近6场交锋分差+最近6场主客交锋分差+最近6场交锋进球差+最近6场主客交锋进球差	*/
	/*	F2=3场																*/
	/*	F3=最近一场															*/
	/*																		*/
	/*  n2 最近6场交锋胜负差                                                */
	/*  n3 最近6场相同交锋胜负差                                            */
	/*	f61	最近6场交锋进球差												*/
	/*	f62	最近6场主客交锋进球差											*/
	/*  f31 最近3场交锋胜负差                                               */
	/*  f32 最近3场相同交锋胜负差                                           */
	/*	f33	最近3场交锋进球差												*/
	/*	f34	最近3场主客交锋进球差											*/
	/*  n8 最近一场交锋胜负差                                               */
	/*  f11 最近一场主客交锋胜负差                                          */
	/*	f12	最近1场交锋进球差												*/
	/*	f13	最近1场主客交锋进球差											*/
	/*																		*/
	/*  6.K=K1*40%+K2*40%+K3*20%											*/
	/*	K1=最近6场得分差+最近6场主客得分差+最近6场进球差+最近6场主客进球差	*/
	/*  K2=3场																*/
	/*  K3=最近一场															*/
	/*																		*/
	/*  n4：最近6场积分差                                                   */
	/*  n6：最近6场主客场积分差                                             */
	/*   n5：最近6场本队进球数差                                            */
	/*   n7：最近6场主客场进球数差                                          */
	/*																		*/
	/*  k31：最近3场积分差                                                   */
	/*  k32：最近3场主客场积分差                                             */
	/*	k33 最近3场进球数差													*/
	/*	k34 最近3场主客场进球数差											*/
	/*																		*/
	/*   n9：最近一场胜负差                                                 */
	/*  k11：最近1场主客场积分差                                             */
	/*   n10：最近一场本队进球数差                                          */
	/*	k12 最近1场主客场进球数差											*/
	/*																		*/
	/*																		*/
	/*																		*/
	/*																		*/
	/*																		*/
	/*	Z1主队																*/
	/*	Z2主队上半															*/
	/*	G1客队																*/
	/*	G2客队上半   														*/
	/*																		*/
	/*																		*/
	/*																		*/
	/*																		*/
	/************************************************************************/
	if (match == 0)
		return;

	int fullCount = 0;//统计数据完整度
	int nSize = 0, nSize2 = 0;
	int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0;
	double f31=0,f32=0,f33=0,f34=0;
	double f61=0,f62=0;
	double f11=0,f12=0,f13=0;
	double a=0,b=0,c=0;
	double da =0,db=0,dc=0;
	double f1=0,f2=0,f3=0;
	double k31=0,k32=0,k33=0,k34=0;
	double Win1=0,Lose1=0,Win2=0,Lose2=0;
	double Dql1=0, Dql2=0;

	double k1=0,k2=0,k3=0;
	double k11=0,k12=0;


	Team* homeTeam = match->homeTeam();
	Team* guestTeam = match->guestTeam();
	MatchParameter* matchParameter = new MatchParameter;
// 	MatchParameter* matchParameter = match->matchParameter();

	vector<Match*> jiaoFengRecord = match->jiaoFengRecord();
	vector<Match*> jiaoFengRecordSame = match->jiaoFengRecordSame();
	vector<Match*> homeRecord = match->homeRecord();
	vector<Match*> homeRecordSame = match->homeRecordSame();
	vector<Match*> guestRecord = match->guestRecord();
	vector<Match*> guestRecordSame = match->guestRecordSame();

	//n1
	n1 = homeTeam->leagueData()->jiFen() -guestTeam->leagueData()->jiFen();
	if (homeTeam->leagueData()->finishNum() > 0)
		fullCount++;
	if (guestTeam->leagueData()->finishNum() > 0)
		fullCount++;

	//n2, n8, a
	int aa3=0,aa6=0;
	int dd3=0,dd6=0;
	nSize = (jiaoFengRecord.size()>6) ? 6 :jiaoFengRecord.size();
	fullCount += nSize;
	for (int i=0; i<nSize; i++)
	{
		Match* pMat = jiaoFengRecord[i];
		BOOL bSame = (homeTeam->id() == pMat->homeTeam()->id())?TRUE:FALSE;
		if (pMat->homeScore()!=pMat->guestScore())//分胜负
		{
			if ((pMat->homeScore() > pMat->guestScore())==bSame)
			{
				n2 += 3;
				if (i==0)
					n8=3;
				if (i<3)
					f31+=3;
			}
			else
			{
				n2 -= 3;
				if (i==0)
					n8=-3;
				if (i<3)
					f31 -= 3;
			}

			if (bSame)
			{
				f61 += (pMat->homeScore() - pMat->guestScore());
				if (i<3)
					f33 += (pMat->homeScore() - pMat->guestScore());
				if (i==0)
					f12 +=(pMat->homeScore() - pMat->guestScore());
			}
			else
			{
				f61 +=(pMat->guestScore()-pMat->homeScore());
				if (i<3)
					f33+=(pMat->guestScore()-pMat->homeScore());
				if (i==0)
					f12 +=(pMat->guestScore()-pMat->homeScore());
			}
		}
		aa6+= (pMat->homeScore() + pMat->guestScore());
		if (i<3)
			aa3+= (pMat->homeScore() + pMat->guestScore());

		//d
		if ((pMat->homeScore() + pMat->guestScore())>2)
		{
			if (i<3)
				dd3++;
			dd6++;
		}
	}//end for
	if (nSize>3)
	{
		a = ((double)aa3/3+(double)aa6/nSize)/2;
		da = ((double)dd3/3+(double)dd6/nSize)/2;
	}
	else if (nSize>0)	
	{
		a = ((double)(aa3+aa6)/nSize)/2;
		da = ((double)(dd3+dd6)/nSize)/2;
	}
	else
	{
		a = 0;
		da = 0;
	}

	//n3
	nSize = (jiaoFengRecordSame.size()>6) ? 6:jiaoFengRecordSame.size();
	fullCount += nSize;
	for (int i=0; i<nSize; i++)
	{
		Match* pMat = jiaoFengRecordSame[i];

		if (pMat->homeScore()>pMat->guestScore())
		{
			n3 += 3;
			if (i<3)
				f32+=3;
			if (i==0)
				f11 = 3;
		}
		else if (pMat->homeScore()<pMat->guestScore())
		{
			n3 -= 3;
			if (i<3)
				f32-=3;
			if (i==0)
				f11 = -3;
		}

		f62 +=(pMat->homeScore() - pMat->guestScore());
		if (i<3)
			f34 += (pMat->homeScore() - pMat->guestScore());
		if (i==0)
			f13 = (pMat->homeScore() - pMat->guestScore());
	}

	f1 = n2+n3+f61+f62;
	f2 = f31+f32+f33+f34;
	f3 = n8+f11+f12+f13;
 	matchParameter->setParameterF(f1*0.4+f2*0.4+f3*0.2);

	//n9,n10
	int nChangCi6=0,nChangCi12=0;
	int bb6=0,cc3=0;
	int db6=0, dc3=0;
	int nZhuIn6=0,nZhuLose6=0,nZhuInHarf6=0,nZhuLoseHarf6=0;
	int nKeIn6=0,nKeLose6=0,nKeInHarf6=0,nKeLoseHarf6=0;

	nSize = (homeRecord.size()>6) ? 6:homeRecord.size();
	fullCount += nSize;

	for (int i=0; i<nSize; i++)
	{
		Match* pMat = homeRecord[i];
		BOOL bSame = (homeTeam->id() == pMat->homeTeam()->id())?TRUE:FALSE;
		if (pMat->homeScore()!=pMat->guestScore())
		{
			if ((pMat->homeScore() > pMat->guestScore())==bSame)//win
			{
				n4 += 3;
				if (i==0)
					n9 = 3;
				if (i<3)
					k31+=3;
			}

			if (bSame)
			{
				n5 += pMat->homeScore();

				nZhuIn6+=pMat->homeScore();
				nZhuLose6+=pMat->guestScore();
				nZhuInHarf6+=pMat->homeScoreHarf();
				nZhuLoseHarf6+=pMat->guestScoreHarf();

				if (i==0)
					n10 = pMat->homeScore();
				if (i<3)
					k33+= pMat->homeScore();
			}
			else
			{
				n5 += pMat->guestScore();

				nZhuIn6+=pMat->guestScore();
				nZhuLose6+=pMat->homeScore();
				nZhuInHarf6+=pMat->guestScoreHarf();
				nZhuLoseHarf6+=pMat->homeScoreHarf();

				if (i==0)
					n10 = pMat->guestScore();
				if (i<3)
					k33+= pMat->guestScore();
			}
		}
		else//ping
		{
			nZhuIn6+=pMat->homeScore();
			nZhuLose6+=pMat->guestScore();
			nZhuInHarf6+=pMat->homeScoreHarf();
			nZhuLoseHarf6+=pMat->guestScoreHarf();

			n4 += 1;
			n5 += pMat->homeScore();
			if (i<3)
				k31+=1;

			if (i==0)
			{
				n9 = 1;
				n10 = pMat->homeScore();
			}
			if (i<3)
				k33+=pMat->homeScore();
		}

		bb6 += (pMat->homeScore() + pMat->guestScore());
		if (i<3)
		{
			cc3 += (pMat->homeScore() + pMat->guestScore());
			nChangCi6++;
		}
		nChangCi12++;

		//d
		if ((pMat->homeScore() + pMat->guestScore())>2)
		{
			if (i<3)
				dc3++;
			db6++;
		}
	}

	nSize2 = (guestRecord.size()>6) ? 6:guestRecord.size();
	fullCount += nSize2;
	for (int i=0; i<nSize2; i++)
	{
		Match* pMat = guestRecord[i];
		BOOL bSame = (guestTeam->id() == pMat->guestTeam()->id())?TRUE:FALSE;
		if (pMat->homeScore() != pMat->guestScore())
		{
			if ((pMat->homeScore() > pMat->guestScore())!=bSame)//win
			{
				n4 -= 3;
				if (i==0)
					n9 -= 3;
				if (i<3)
					k31-=3;
			}
			if (bSame)
			{
				n5 -= pMat->guestScore();

				nKeIn6+=pMat->guestScore();
				nKeLose6+=pMat->homeScore();
				nKeInHarf6+=pMat->guestScoreHarf();
				nKeLoseHarf6+=pMat->homeScoreHarf();

				if (i==0)
					n10 -= pMat->guestScore();
				if (i<3)
					k33-= pMat->guestScore();

			}
			else
			{
				n5 -= pMat->homeScore();

				nKeIn6+=pMat->homeScore();
				nKeLose6+=pMat->guestScore();
				nKeInHarf6+=pMat->homeScoreHarf();
				nKeLoseHarf6+=pMat->guestScoreHarf();

				if (i==0)
					n10 -= pMat->homeScore();
				if (i<3)
					k33-=pMat->homeScore();
			}
		}
		else//ping
		{
			n4 -= 1;
			n5 -= pMat->homeScore();

			nKeIn6+=pMat->guestScore();
			nKeLose6+=pMat->homeScore();
			nKeInHarf6+=pMat->guestScoreHarf();
			nKeLoseHarf6+=pMat->homeScoreHarf();

			if (i<3)
			{
				k31-=1;
				k33-=pMat->homeScore();
			}

			if (i==0)
				n9 -= 1;
		}

		bb6 += (pMat->homeScore() + pMat->guestScore());
		if (i<3)
		{
			cc3 += (pMat->homeScore() + pMat->guestScore());
			nChangCi6++;
		}
		nChangCi12++;

		//d
		if ((pMat->homeScore() + pMat->guestScore())>2)
		{
			if (i<3)
				dc3++;
			db6++;
		}
	}
	int x1=0;
	if (nSize>3)
		x1=3;
	else
		x1 = nSize;
	if (nSize2>3)
		x1+=3;
	else
		x1+=nSize2;

	if ((nSize+nSize2) == 0)
	{
		b=0;
		db = 0;
	}
	else
	{
		b = (double)bb6/(nSize+nSize2);
		db = (double)db6/(nSize+nSize2);
	}

	if (x1==0)
	{
		c=0;
		dc=0;
	}
	else
	{
		c = (double)cc3/x1;
		dc = (double)dc3/x1;
	}

	double nZhuInPer6=0,nZhuLosePer6=0,nZhuInHarfPer6=0,nZhuLoseHarfPer6=0;
	BOOL bLoseData=FALSE;
	if (nSize==6)
	{
		nZhuInPer6 = (double)nZhuIn6/6;
		nZhuLosePer6 = (double)nZhuLose6/6;
		nZhuInHarfPer6 = (double)nZhuInHarf6/6;
		nZhuLoseHarfPer6 = (double)nZhuLoseHarf6/6;
	}
	else
		bLoseData=TRUE;
	double nKeInPer6=0,nKeLosePer6=0,nKeInHarfPer6=0,nKeLoseHarfPer6=0;
	if (nSize2==6)
	{
		nKeInPer6 = (double)nKeIn6/6;
		nKeLosePer6 = (double)nKeLose6/6;
		nKeInHarfPer6 = (double)nKeInHarf6/6;
		nKeLoseHarfPer6 = (double)nKeLoseHarf6/6;
	}
	else
		bLoseData=TRUE;


	int nZhuIn=0,nZhuLose=0,nZhuInHarf=0,nZhuLoseHarf=0;
	int nKeIn=0,nKeLose=0,nKeInHarf=0,nKeLoseHarf=0;

	nSize = (homeRecord.size()>=20) ? homeRecord.size():0;//取20场数据
	for (int i=0; i<nSize; i++)
	{
		Match* pMat = homeRecord[i];
		BOOL bSame = (homeTeam->id() == pMat->homeTeam()->id())?TRUE:FALSE;
		if (bSame)
		{
			nZhuIn+=pMat->homeScore();
			nZhuLose+=pMat->guestScore();
			nZhuInHarf+=pMat->homeScoreHarf();
			nZhuLoseHarf+=pMat->guestScoreHarf();				
		}
		else
		{
			nZhuIn+=pMat->guestScore();
			nZhuLose+=pMat->homeScore();
			nZhuInHarf+=pMat->guestScoreHarf();
			nZhuLoseHarf+=pMat->homeScoreHarf();
		}
	}

	nSize2 = (guestRecord.size()>=20) ? guestRecord.size():0;
	for (int i=0; i<nSize2; i++)
	{
		Match* pMat = guestRecord[i];
		BOOL bSame = (guestTeam->id() == pMat->guestTeam()->id())?TRUE:FALSE;
		if (bSame)
		{
			nKeIn+=pMat->guestScore();
			nKeLose+=pMat->homeScore();
			nKeInHarf+=pMat->guestScoreHarf();
			nKeLoseHarf+=pMat->homeScoreHarf();

		}
		else
		{
			nKeIn+=pMat->homeScore();
			nKeLose+=pMat->guestScore();
			nKeInHarf+=pMat->homeScoreHarf();
			nKeLoseHarf+=pMat->guestScoreHarf();
		}
	}

	//场均
	double nZhuInPer=0,nZhuLosePer=0,nZhuInHarfPer=0,nZhuLoseHarfPer=0;
	if (nSize>=20)
	{
		nZhuInPer = (double)nZhuIn/nSize;
		nZhuLosePer = (double)nZhuLose/nSize;
		nZhuInHarfPer = (double)nZhuInHarf/nSize;
		nZhuLoseHarfPer = (double)nZhuLoseHarf/nSize;
	}
	else
		bLoseData=TRUE;
	double nKeInPer=0,nKeLosePer=0,nKeInHarfPer=0,nKeLoseHarfPer=0;
	if (nSize2>=20)
	{
		nKeInPer = (double)nKeIn/nSize2;
		nKeLosePer = (double)nKeLose/nSize2;
		nKeInHarfPer = (double)nKeInHarf/nSize2;
		nKeLoseHarfPer = (double)nKeLoseHarf/nSize2;
	}
	else
		bLoseData=TRUE;

	if (!bLoseData)
	{
		double nZhuInKLL=0,nZhuLoseKLL=0, nZhuInHarfKLL=0,nZhuLoseHarfKLL=0;
		double nKeInKLL=0,nKeLoseKLL=0,nKeInHarfKLL=0,nKeLoseHarfKLL=0;

		if (nZhuInPer!=0)
			nZhuInKLL = (nZhuInPer6-nZhuInPer)/nZhuInPer;
		if (nZhuLosePer!=0)
			nZhuLoseKLL = (nZhuLosePer6 - nZhuLosePer)/nZhuLosePer;
		if (nZhuInHarfKLL!=0)
			nZhuInHarfKLL = (nZhuInHarfPer6-nZhuInHarfPer)/nZhuInHarfPer;
		if (nZhuLoseHarfPer!=0)
			nZhuLoseHarfKLL = (nZhuLoseHarfPer6-nZhuLoseHarfPer)/nZhuLoseHarfPer;

		if (nKeInPer!=0)
			nKeInKLL = (nKeInPer6-nKeInPer)/nKeInPer;
		if (nKeLosePer!=0)
			nKeLoseKLL = (nKeLosePer6-nKeLosePer)/nKeLosePer;
		if (nKeInHarfPer!=0)
			nKeInHarfKLL = (nKeInHarfPer6-nKeInHarfPer)/nKeInHarfPer;
		if (nKeLoseHarfPer!=0)
			nKeLoseHarfKLL = (nKeLoseHarfPer6-nKeLoseHarfPer)/nKeLoseHarfPer;

		matchParameter->setZ1(nZhuInPer*(1+nZhuInKLL+nKeLoseKLL));
		matchParameter->setG1(nKeInPer*(1+nZhuLoseKLL+nKeInKLL));
		matchParameter->setZ2(nZhuInHarfPer*(1+nZhuInHarfKLL+nKeLoseHarfKLL));
		matchParameter->setG2(nKeInHarfPer*(1+nZhuLoseHarfKLL+nKeInHarfKLL));
	}

	//n6,n7
	nSize = (homeRecordSame.size()>6) ? 6:homeRecordSame.size();
	fullCount += nSize;
	for (int i=0; i<nSize; i++)
	{
		Match* pMat = homeRecordSame[i];
		if (pMat->homeScore() > pMat->guestScore())//win
		{
			n6 += 3;
			if (i<3)
				k32+=3;
			if (i==0)
				k11 = 3;
		}
		else if (pMat->homeScore() == pMat->guestScore())
		{
			n6 += 1;
			if (i<3)
				k32+=1;
			if (i==0)
				k11 = 1;
		}
		n7 += pMat->homeScore();
		if (i<3)
			k34+=pMat->homeScore();
		if (i==0)
			k12 = pMat->homeScore();
	}

	nSize2 = (guestRecordSame.size()>6) ? 6:guestRecordSame.size();
	fullCount += nSize2;
	for (int i=0; i<nSize2; i++)
	{
		Match* pMat = guestRecordSame[i];
		BOOL bSame = (guestTeam->id() == pMat->guestTeam()->id())?TRUE:FALSE;
		if (pMat->homeScore()< pMat->guestScore())//lose
		{
			n6 -= 3;
			if (i<3)
				k32-=3;
			if (i==0)
				k11-=3;
		}
		else if (pMat->homeScore() == pMat->guestScore())
		{
			n6 -= 1;
			if (i<3)
				k32-=1;
			if (i==0)
				k11-=1;
		}

		n7 -= pMat->guestScore();
		if (i<3)
			k34-=pMat->guestScore();
		if (i==0)
			k12 -=pMat->guestScore();
	}

	k1 = n4+n5+n6+n7;
	k2 = k31+k32+k33+k34;
	k3 = n9+n10+k11+k12;
	matchParameter->setParameterK(k1*0.4+k2*0.4+k3*0.2);

	matchParameter->setParameterJ(n1+n2+n3+n4+n5+n6+n7+n8+n9+n10);
	if (jiaoFengRecord.size()<=0)
		matchParameter->setParameterH((a+b+c)/2);
	else
		matchParameter->setParameterH((a+b+c)/3);
	if (jiaoFengRecord.size()<=0)
		matchParameter->setParameterD((da+db+dc)/2);
	else
		matchParameter->setParameterD((da+db+dc)/3);

	matchParameter->setFullData((double)fullCount / 38);

	nSize = (homeRecord.size()>10) ? 10:homeRecord.size();
	for (int i=0; i<nSize; i++)
	{
		Match* pMat = homeRecord[i];
		BOOL bSame = (homeTeam->id() == pMat->homeTeam()->id())?TRUE:FALSE;
		if (pMat->homeScore()!= pMat->guestScore())
		{
			if (bSame)
			{
				Win1+=pMat->homeScore();
				Lose1+=pMat->guestScore();
			}
			else
			{
				Win1+=pMat->guestScore();
				Lose1+=pMat->homeScore();
			}
		}
		else//ping
		{
			Win1+=pMat->homeScore();
			Lose1+=pMat->guestScore();
		}

		//d
		if ((pMat->homeScore() + pMat->guestScore())>2)
		{
			Dql1++;
		}
	}
	if (nSize==0)
	{
		Dql1 = 0;
		Win1 =0;
		Lose1=0;
	}
	else{
		Dql1 = Dql1/nSize;
		Win1 = Win1/nSize;
		Lose1 = Lose1/nSize;
	}

	nSize2 = (guestRecord.size()>10) ? 10:guestRecord.size();
	for (int i=0; i<nSize2; i++)
	{
		Match* pMat = guestRecord[i];
		BOOL bSame = (guestTeam->id() == pMat->guestTeam()->id())?TRUE:FALSE;
		if (pMat->homeScore()!= pMat->guestScore())
		{
			if (bSame)
			{
				Win2+=pMat->guestScore();
				Lose2+=pMat->homeScore();
			}
			else
			{
				Win2+=pMat->homeScore();
				Lose2+=pMat->guestScore();
			}
		}
		else//ping
		{
			Win2+=pMat->guestScore();
			Lose2+=pMat->homeScore();
		}

		//d
		if ((pMat->homeScore() + pMat->guestScore())>2)
		{
			Dql2++;
		}
	}

	if (nSize2==0)
	{
		Dql2=0;
		Win2=0;
		Lose2=0;
	}
	else{
		Dql2 = Dql2/nSize2;
		Win2 = Win2/nSize2;
		Lose2= Lose2/nSize2;
	}

	matchParameter->setParameterT((Win1+Lose1+Win2+Lose2)*(Dql1+Dql2)/2);
	match->setMatchParameter(matchParameter);
}

void calculate(Match* match)
{

}

void calculateBaseData(Match* match)
{
	/************************************************************************/
	/*  1、基本面     n1+n2+n3+n4+n5+n6+n7+n8+n9+n10                        */
	/*   n1：当前联赛积分差                                                 */
	/*   n2：最近6场交锋胜负差                                              */
	/*   n3：最近6场相同交锋胜负差                                          */
	/*   n4：最近6场积分差。主队胜+3，主队平+1，客队胜-3，客队平-1            */
	/*   n5：最近6场本队进球数差                                            */
	/*   n6：最近6场主客场积分差                                            */
	/*   n7：最近6场主客场进球数差                                          */
	/*   n8：最近一场交锋胜负差                                             */
	/*   n9：最近一场胜负差                                                 */
	/*   n10：最近一场本队进球数差                                          */
	/*                                                                      */
	/*  2、大小球 (a+b+c)/3                                                 */
	/*  a：双方最近交锋6场得失球数/6+双方最近交锋3场得失球数/3）/2          */
	/*  b：双方最近6场比赛得失球数/12                                       */
	/*  c：双方最近3场比赛得失球数/6                                        */
	/*                                                                      */
	/*  3、大球率   (da+db+dc)/3                                            */
	/*  da：双方最近交锋6场大球场次数/6+双方最近交锋3场大球场次数/3）/2     */
	/*  db：双方最近6场比赛大球场次数/12                                    */
	/*  dc：双方最近3场比赛大球场次数/6                                     */
	/*																		*/
	/*	4.进球率 ()															*/
	/*	Win1	主队最近10场进球数										    */
	/*	Lose1	主队最近10场失球数											*/
	/*	Win2	客队最近10场进球数											*/
	/*	Lose2	客队最近10场失球数											*/
	/*	Dxl1																*/
	/*	Dql2																*/
	/*																		*/
	/*  5.F=F1*40%+F2*40%+F3*20%											*/
	/*  F1=最近6场交锋分差+最近6场主客交锋分差+最近6场交锋进球差+最近6场主客交锋进球差	*/
	/*	F2=3场																*/
	/*	F3=最近一场															*/
	/************************************************************************/






}

// void CalculateZG(Match* match)
// {
// }