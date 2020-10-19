// ProgramTransformation.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "LogFileException.h"
using namespace std;

#include "LogFile.h"

int main()
{
    {
        try
        {
            LogFile dummy;
            dummy.write("Writing from main");
        }
        catch (const log_file_exception& e)
        {
            cerr << e.what() << endl;
        }

    }

    try
    {
        LogFile logFile("Exceptions.log");
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
}
