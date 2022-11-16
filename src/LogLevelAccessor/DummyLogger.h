#pragma once
#include <fstream>

#include "ILogger.h"

#ifdef LOGLEVELACCESSOR_EXPORTS
	#define DUMMYLOGGER_API __declspec(dllexport) 
#else
	#define DUMMYLOGGER_API __declspec(dllimport) 
#endif

class DUMMYLOGGER_API DummyLogger final : public ILogger
{
public:
	DummyLogger();
	~DummyLogger() override;

	//disable copy, move operators
	DummyLogger(const DummyLogger&) = delete;
	DummyLogger &operator=(const DummyLogger&) = delete;
	DummyLogger(DummyLogger&&) = delete;
	DummyLogger &operator=(DummyLogger&&) = delete;

	void WriteInfo(const std::string& logMessage) override;

private:
	std::ofstream logFile;
};

