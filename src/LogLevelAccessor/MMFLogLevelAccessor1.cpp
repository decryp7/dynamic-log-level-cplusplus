#include "pch.h"
#include "MMFLogLevelAccessor1.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tchar.h>
#include <chrono>
#include "MMFLogLevelAccessor.h"

MMFLogLevelAccessor1::MMFLogLevelAccessor1() : cachedLogLevel(0)
{
	logLevelChangeEvent = CreateEvent(
		NULL,               // default security attributes
		FALSE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("LogLevelChangedEvent")  // object name
	);

	if (logLevelChangeEvent == nullptr)
	{
		throw std::exception(("Could not create LogLevelChangedEvent. " + std::to_string(GetLastError())).c_str());
	}

	//Refer to https://learn.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szName);                 // name of mapping object

	if (hMapFile == nullptr)
	{
		throw std::exception(("Could not create file mapping object. " + std::to_string(GetLastError())).c_str());
	}

	pBuf = static_cast<LPTSTR>(MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE));

	if (pBuf == nullptr)
	{
		throw std::exception(("Could not map view of file. " + std::to_string(GetLastError())).c_str());
	}

	monitorLogLevelChangeEventThread = std::thread(&MMFLogLevelAccessor1::UpdateLogLevel, this);
}

MMFLogLevelAccessor1::~MMFLogLevelAccessor1()
{
	//std::cout << "destructor is called!" << std::endl;
	stopMonitoring = true;
	monitorLogLevelChangeEventThread.join();

	if(logLevelChangeEvent != nullptr)
	{
		CloseHandle(logLevelChangeEvent);
	}

	if (pBuf != nullptr)
	{
		UnmapViewOfFile(pBuf);
	}

	if (hMapFile != nullptr)
	{
		CloseHandle(hMapFile);
	}
}

int MMFLogLevelAccessor1::GetLogLevel()
{
	return cachedLogLevel;
}

void MMFLogLevelAccessor1::SetLogLevel(const int logLevel)
{
	const std::wstring s = std::to_wstring(logLevel);
	const auto cs = s.c_str();
	//Do not write more then buffer size
	CopyMemory((PVOID)pBuf, cs, BUF_SIZE);

	if (!SetEvent(logLevelChangeEvent))
	{
		throw std::exception(("Could not set LogLevelChangeEvent. " + std::to_string(GetLastError())).c_str());
	}
}

void MMFLogLevelAccessor1::UpdateLogLevel()
{
	while (TRUE) {
		if(stopMonitoring)
		{
			break;
		}

		if (WaitForSingleObject(logLevelChangeEvent, 10) == WAIT_OBJECT_0) {
			//Any better way to do this?
			//Do not read more then buffer size
			const auto copy = new TCHAR[BUF_SIZE];
			for (int i = 0; i < BUF_SIZE; i++)
			{
				copy[i] = pBuf[i];
			}
			cachedLogLevel = _ttoi(copy);
		}
	}
}

