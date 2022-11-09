// ChangeLogLevel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "ILogLevelAccessor.h"
#include "MMFLogLevelAccessor.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		cout << "Missing log level argument" << endl;
		return 0;
	}

    if(isdigit(*argv[1]))
    {
	    const int logLevel = std::stoi(argv[1]);
		cout << "Changing log level to " << argv[1] << endl;
		try 
		{
			const std::unique_ptr<ILogLevelAccessor> logAccessor = std::make_unique<MMFLogLevelAccessor>();
			logAccessor->SetLogLevel(logLevel);
		}catch (std::exception &ex)
		{
			cout << ex.what() << endl;
		}
    }else
    {
		cout << "The argument (" << argv[1] << ") is not valid." << endl;
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
