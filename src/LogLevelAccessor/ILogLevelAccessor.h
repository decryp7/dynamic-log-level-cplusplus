#pragma once


#ifdef LOGLEVELACCESSOR_EXPORTS
#define ILOGLEVELACCESSOR_API __declspec(dllexport) 
#else
#define ILOGLEVELACCESSOR_API __declspec(dllimport) 
#endif

class ILOGLEVELACCESSOR_API ILogLevelAccessor
{
public:
	virtual ~ILogLevelAccessor() = default;

	/**
	 * \brief Get the log level
	 * \return 
	 */
	virtual int GetLogLevel() = 0;

	/**
	 * \brief Set the log level
	 * \param logLevel 
	 * \return 
	 */
	virtual void SetLogLevel(int logLevel) = 0;
}; 
