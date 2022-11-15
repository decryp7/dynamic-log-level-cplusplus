#pragma once
#include <atomic>

#include "ILogLevelAccessor.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <mutex>
#include <tchar.h>
#include <thread>

#ifdef LOGLEVELACCESSOR_EXPORTS
#define MMFLOGLEVELACCESSOR1_API __declspec(dllexport) 
#else
#define MMFLOGLEVELACCESSOR1_API __declspec(dllimport) 
#endif

class MMFLOGLEVELACCESSOR1_API  MMFLogLevelAccessor1 final: public ILogLevelAccessor
{
public:
	MMFLogLevelAccessor1();
	~MMFLogLevelAccessor1() override;

	//disable copy, move operators
	MMFLogLevelAccessor1(const MMFLogLevelAccessor1&) = delete;
	MMFLogLevelAccessor1 &operator=(const MMFLogLevelAccessor1&) = delete;
	MMFLogLevelAccessor1(MMFLogLevelAccessor1&&) = delete;
	MMFLogLevelAccessor1 &operator=(MMFLogLevelAccessor1&&) = delete;

	int GetLogLevel() override;
	void SetLogLevel(int logLevel) override;

private:
	void UpdateLogLevel();
	HANDLE hMapFile;
	HANDLE logLevelChangeEvent;
	std::atomic<bool> stopMonitoring = false;
	std::thread monitorLogLevelChangeEventThread;
	LPCTSTR pBuf;
	std::atomic<int> cachedLogLevel;
	static constexpr TCHAR szName[] = TEXT("MyLogLevelAccessor");
};

