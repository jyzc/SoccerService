#ifndef _MATCH_ALGORITHM_H__
#define _MATCH_ALGORITHM_H__
#pragma once

//���������C++����������ô����ΪC���ӷ�ʽ
#ifdef __cplusplus
extern "C" {
#endif



// ͨ�����������ǵ��뻹�ǵ���
#ifdef _MATCH_ALGORITHM
#define MATCH_ALGORITHM_API __declspec(dllexport)
#else
#define MATCH_ALGORITHM_API __declspec(dllimport)
#endif

#include "..\\..\\SoccerService\\SoccerService\\WXZMatch.h"
// ����/���뺯������

MATCH_ALGORITHM_API void CalculateH(Match* match);




#undef MATCH_ALGORITHM_API



#ifdef __cplusplus
}
#endif

#endif	//_MATCH_ALGORITHM_H__