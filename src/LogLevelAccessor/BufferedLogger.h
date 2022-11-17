#pragma once

#ifdef LOGLEVELACCESSOR_EXPORTS
#define BUFFEREDLOGGER_API __declspec(dllexport) 
#else
#define BUFFEREDLOGGER_API __declspec(dllimport) 
#endif
#include <atomic>
#include <fstream>
#include <mutex>
#include <queue>
#include <thread>
#include <sstream> 

#include "ILogger.h"

class BUFFEREDLOGGER_API BufferedLogger final : public ILogger
{
public:
	BufferedLogger();
	~BufferedLogger() override;

	//disable copy, move operators
	BufferedLogger(const BufferedLogger&) = delete;
	BufferedLogger  &operator=(const BufferedLogger&) = delete;
	BufferedLogger(BufferedLogger&&) = delete;
	BufferedLogger  &operator=(BufferedLogger&&) = delete;

	void WriteInfo(const std::string& logMessage) override;

private:
	void MonitorIncomingQueue();
	std::queue<std::string> *incoming;
	std::queue<std::string> *outgoing;
	std::thread monitorIncomingQueueThread;
	std::atomic<bool> stopMonitoring;
	std::mutex lockMutex;
	std::ofstream logFile;
	std::stringstream outgoingStream;
	size_t bufferSize;
};

