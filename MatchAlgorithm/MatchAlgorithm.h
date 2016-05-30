#ifndef _MATCH_ALGORITHM_H__
#define _MATCH_ALGORITHM_H__
#pragma once

//如果定义了C++编译器，那么声明为C链接方式
#ifdef __cplusplus
extern "C" {
#endif



// 通过宏来控制是导入还是导出
#ifdef _MATCH_ALGORITHM
#define MATCH_ALGORITHM_API __declspec(dllexport)
#else
#define MATCH_ALGORITHM_API __declspec(dllimport)
#endif

#include "..\\..\\SoccerService\\SoccerService\\WXZMatch.h"
// 导出/导入函数声明

MATCH_ALGORITHM_API void CalculateH(Match* match);




#undef MATCH_ALGORITHM_API



#ifdef __cplusplus
}
#endif

#endif	//_MATCH_ALGORITHM_H__