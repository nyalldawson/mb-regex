#ifndef __MAIN_H__
#define __MAIN_H__

#include <string>
#include <boost/regex.hpp>
#include <windows.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

int DLL_EXPORT regex_test(char * s_input, char * s_match);
const char* DLL_EXPORT regex_match(char * s_input, char * s_match);
int DLL_EXPORT regex_match_multiple(char * s_input, char * s_match, char * s_matches[]);
int DLL_EXPORT regex_match_all(char * s_input, char * s_match, char * s_matches[]);
int DLL_EXPORT regex_replace(char * s_input, char * s_match, char * s_replace, char * s_dest);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
