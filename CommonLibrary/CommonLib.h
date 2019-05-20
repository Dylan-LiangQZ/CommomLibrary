#pragma once

#ifdef _COMMON_DLL
#define COMMON_DLL_SPEC __declspec(dllexport)
#else
#define COMMON_DLL_SPEC __declspec(dllimport)
#endif