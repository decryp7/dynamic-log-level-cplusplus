// DynamicLogging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ILogLevelAccessor.h"
#include "MMFLogLevelAccessor.h"
#include "MMFLogLevelAccessor1.h"

using std::cout;
using std::endl;

int main()
{
	try {
		const std::unique_ptr<ILogLevelAccessor> logAccessor = std::make_unique<MMFLogLevelAccessor1>();

		while (true)
		{
			const int logLevel = logAccessor->GetLogLevel();
			cout << "logAccessor logLevel: " << logLevel << endl;
			switch (logLevel)
			{
				case 0:
					cout << "LogLevel: Info" << endl;
					break;
				case 1:
					cout << "LogLevel: Debug" << endl;
					break;
				case 2:
					cout << "LogLevel: Trace" << endl;
					break;
				default:
					cout << "Unknown option..." << endl;
			}
			Sleep(1 * 1000);
		}
	}
	catch (std::exception &ex)
	{
		cout << ex.what() << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
