#pragma once
#include "ILogLevelAccessor.h"

#ifdef LOGLEVELACCESSOR_EXPORTS
#define DUMBLOGLEVELACCESSOR_API __declspec(dllexport) 
#else
#define DUMBLOGLEVELACCESSOR_API __declspec(dllimport) 
#endif

class DUMBLOGLEVELACCESSOR_API  DumbLogLevelAccessor final : public ILogLevelAccessor
{
public:
	DumbLogLevelAccessor() : logLevel(1){}
	~DumbLogLevelAccessor() override = default;

	//disable copy, move operators
	DumbLogLevelAccessor(const DumbLogLevelAccessor&) = delete;
	DumbLogLevelAccessor &operator=(const DumbLogLevelAccessor&) = delete;
	DumbLogLevelAccessor(DumbLogLevelAccessor&&) = delete;
	DumbLogLevelAccessor &operator=(DumbLogLevelAccessor&&) = delete;

	int GetLogLevel() override;
	void SetLogLevel(int logLevel) override;

private:
	int logLevel;
};
