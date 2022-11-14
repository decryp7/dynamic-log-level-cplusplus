#include "pch.h"
#include "MMFLogLevelAccessor.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tchar.h>

MMFLogLevelAccessor::MMFLogLevelAccessor()
{
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

	if(pBuf == nullptr)
	{
		throw std::exception(("Could not map view of file. " + std::to_string(GetLastError())).c_str());
	}
}

MMFLogLevelAccessor::~MMFLogLevelAccessor()
{
	std::cout << "destructor is called!" << std::endl;
	if(pBuf != nullptr) 
	{
		UnmapViewOfFile(pBuf);
	} 

	if(hMapFile != nullptr)
	{
		CloseHandle(hMapFile);
	}
}

int MMFLogLevelAccessor::GetLogLevel()
{
	//Any better way to do this?
	//Do not read more then buffer size
	const auto copy = new TCHAR[BUF_SIZE];
	for (int i=0; i < BUF_SIZE; i++)
	{
		copy[i] = pBuf[i];
	}
	return _ttoi(copy);
}

void MMFLogLevelAccessor::SetLogLevel(const int logLevel)
{
	std::wstring s = std::to_wstring(logLevel);
	auto cs = s.c_str();
	//Do not write more then buffer size
	CopyMemory((PVOID)pBuf, cs, BUF_SIZE);
}

