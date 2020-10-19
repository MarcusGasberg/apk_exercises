
#if !defined(_LOGFILE_H_)
#define _LOGFILE_H_

#include <string>
#include <stdexcept>

class LogFile
{
public:
	void write( const std::string& data );
	void init( const std::string& logfilename );
    

	LogFile();
	explicit LogFile( const std::string& logfilename );
	~LogFile();

private:
	std::string logfilename_;
	void internalWrite( const std::string& data );
};

#endif // !defined(AFX_LOGFILE_H__4A9D73D5_7588_11D3_A2E2_00104BB8D7A4__INCLUDED_)
