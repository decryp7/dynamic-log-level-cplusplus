#pragma once
#include <string>

#ifdef LOGLEVELACCESSOR_EXPORTS
	#define ILOGGER_API __declspec(dllexport) 
#else
	#define ILOGGER_API __declspec(dllimport) 
#endif

class ILOGGER_API ILogger
{
public:
	virtual ~ILogger() = default;

	virtual void WriteInfo(const std::string &logMessage) = 0;
};

