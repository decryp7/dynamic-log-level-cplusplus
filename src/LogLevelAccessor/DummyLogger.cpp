#include "pch.h"
#include "DummyLogger.h"

#include <iostream>

DummyLogger::DummyLogger() : logFile("dummylogs.txt")
{
	
}

DummyLogger::~DummyLogger()
{
	logFile.close();
}


void DummyLogger::WriteInfo(const std::string& logMessage)
{
	logFile << logMessage << std::endl;
}
