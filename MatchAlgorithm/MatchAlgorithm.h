#ifndef _MATCH_ALGORITHM_H__
#define _MATCH_ALGORITHM_H__
#pragma once

//如果定义了C++编译器，那么声明为C链接方式
#ifdef __cplusplus
extern "C++" {
#endif


#define _MATCH_ALGORITHM

// 通过宏来控制是导入还是导出
#ifdef _MATCH_ALGORITHM
#define MATCH_ALGORITHM_API __declspec(dllexport)
#else
#define MATCH_ALGORITHM_API __declspec(dllimport)
#endif

// 导出/导入函数声明
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