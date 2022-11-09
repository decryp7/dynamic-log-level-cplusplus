#pragma once
#include "ILogLevelAccessor.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#ifdef LOGLEVELACCESSOR_EXPORTS
	#define MMFLOGLEVELACCESSOR_API __declspec(dllexport) 
#else
	#define MMFLOGLEVELACCESSOR_API __declspec(dllimport) 
#endif

#define BUF_SIZE 2
TCHAR szName[] = TEXT("Global\\MyLogLevelAccessor");

class MMFLOGLEVELACCESSOR_API  MMFLogLevelAccessor : public ILogLevelAccessor
{
public:
	MMFLogLevelAccessor();
	~MMFLogLevelAccessor() override;

	//disable copy, move operators
	MMFLogLevelAccessor(const MMFLogLevelAccessor&) = delete;
	MMFLogLevelAccessor &operator=(const MMFLogLevelAccessor&) = delete;
	MMFLogLevelAccessor(MMFLogLevelAccessor&&) = delete;
	MMFLogLevelAccessor &operator=(MMFLogLevelAccessor&&) = delete;

	int GetLogLevel() override;
	void SetLogLevel(int logLevel) override;

private:
	HANDLE hMapFile;
	LPCTSTR pBuf;
};
