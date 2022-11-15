#include "pch.h"
#include "DumbLogLevelAccessor.h"

int DumbLogLevelAccessor::GetLogLevel()
{
	return this->logLevel;
}

void DumbLogLevelAccessor::SetLogLevel(const int logLevel)
{
	this->logLevel = logLevel;
}
