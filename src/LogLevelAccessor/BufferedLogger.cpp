#include "pch.h"
#include "BufferedLogger.h"

#include <iostream>

BufferedLogger::BufferedLogger() : stopMonitoring(false), logFile("bufferedlogs.txt")
{
	incoming = new std::queue<std::string>;
	outgoing = new std::queue<std::string>;

	monitorIncomingQueueThread = std::thread(&BufferedLogger::MonitorIncomingQueue, this);
}

BufferedLogger::~BufferedLogger()
{
	stopMonitoring = true;
	monitorIncomingQueueThread.join();

	//clear remaining logs
	while (!incoming->empty())
	{
		logFile << incoming->front() << std::endl;
		incoming->pop();
	}

	delete incoming;
	delete outgoing;

	logFile.close();
}

void BufferedLogger::WriteInfo(const std::string& logMessage)
{
	lockMutex.lock();
	incoming->push(logMessage);
	lockMutex.unlock();
}

void BufferedLogger::MonitorIncomingQueue()
{
	while(!stopMonitoring)
	{
		if(incoming->size() > 1000)
		{
			//std::cout << "Buffer full! " << std::to_string(incoming->size()) << std::endl;
			lockMutex.lock();
			const auto old = outgoing;
			outgoing = incoming;
			incoming = old;
			lockMutex.unlock();

			while(!outgoing->empty())
			{
				logFile << outgoing->front() << std::endl;
				outgoing->pop();
			}
		}
	}
}
