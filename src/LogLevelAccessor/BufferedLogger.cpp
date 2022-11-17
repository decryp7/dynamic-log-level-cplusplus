#include "pch.h"
#include "BufferedLogger.h"

#include <iostream>

BufferedLogger::BufferedLogger() :
	stopMonitoring(false),
	logFile("bufferedlogs.txt"),
	bufferSize(1000)
{
	incoming = new std::queue<std::string>;
	outgoing = new std::queue<std::string>;

	monitorIncomingQueueThread = std::thread(&BufferedLogger::MonitorIncomingQueue, this);
}

BufferedLogger::~BufferedLogger()
{
	stopMonitoring = true;
	monitorIncomingQueueThread.join();

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
		if(incoming->size() >= bufferSize)
		{
			//std::cout << "Buffer full! " << std::to_string(incoming->size()) << std::endl;
			lockMutex.lock();

			while (!incoming->empty() && outgoing->size() < bufferSize)
			{
				outgoing->push(incoming->front());
				incoming->pop();
			}

			//const auto old = outgoing;
			//outgoing = incoming;
			//incoming = old;

			lockMutex.unlock();

			//std::cout << "Outgoing buffer size: " << std::to_string(outgoing->size()) << std::endl;
			while(!outgoing->empty())
			{
				//buffer to stringstream
				outgoingStream << outgoing->front() << std::endl;
				outgoing->pop();
			}

			//write out the buffer in stringstream at one go.
			logFile << outgoingStream.rdbuf();
			outgoingStream.str(std::string());
		}
	}

	//std::cout << "Final incoming buffer size: " << std::to_string(incoming->size()) << std::endl;
	//clear remaining logs
	while (!incoming->empty())
	{
		//logFile << incoming->front() << std::endl;
		outgoingStream << incoming->front() << std::endl;
		incoming->pop();
	}
	logFile << outgoingStream.rdbuf();
}
