#ifndef _MATCH_ALGORITHM_H__
#define _MATCH_ALGORITHM_H__
#pragma once

//���������C++����������ô����ΪC���ӷ�ʽ
#ifdef __cplusplus
extern "C++" {
#endif


#define _MATCH_ALGORITHM

// ͨ�����������ǵ��뻹�ǵ���
#ifdef _MATCH_ALGORITHM
#define MATCH_ALGORITHM_API __declspec(dllexport)
#else
#define MATCH_ALGORITHM_API __declspec(dllimport)
#endif

// ����/���뺯������
class Match;
// class MatchParameter;

MATCH_ALGORITHM_API void CalculateH(Match* match);
// MATCH_ALGORITHM_API void CalculateZG(Match* match);

MATCH_ALGORITHM_API void calculate(Match* match);
MATCH_ALGORITHM_API void calculateBaseData(Match* match);



#undef MATCH_ALGORITHM_API



#ifdef __cplusplus
}
#endif

#endif	//_MATCH_ALGORITHM_H__