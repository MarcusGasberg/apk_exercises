
#include <iostream>
#include <fstream>

#include "LogFileException.h"
using namespace std;

#include "LogFile.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogFile::LogFile()
{
	cout << "Creating LogFile Object" << endl;
}

LogFile::LogFile( const string& logfilename )
{
	init( logfilename );
}

LogFile::~LogFile()
{
	cout << "Deleting LogFile Object" << endl;
}

void LogFile::init( const string& logfilename )
{
	logfilename_ = logfilename;
	return internalWrite( "" );
}

void LogFile::write( const string& data )
{
	return internalWrite( data+"\n" );
}

void LogFile::internalWrite( const string& data )
{
	if(logfilename_.empty())
	{
        const auto state = log_file_exception::error_state::filename_is_empty;
		throw log_file_exception(state, logfilename_ + " is empty");
	}
	std::ofstream out;
	out.open( logfilename_.c_str(), std::ofstream::out | std::ofstream::app);
	if( out )
		out << data;
	else
	{
		cerr << "Cannot open file " << logfilename_ << endl;
		const auto state = log_file_exception::error_state::could_not_open_file;
		throw log_file_exception(state, logfilename_ + " could not be opened");
	}
}

