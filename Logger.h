/************************************************

Copyright: SenseTime

Author: Chris Leo

Date:2021-01-09

Description:   this is logger class , it help we debug and save some work 
status when runing 

************************************************/

#pragma once  


#include<string>

#include  "noncopyable.h"

enum LogLevel{
	INFO,  // public work log
	ERROR,  // error log
	FATAL, // coredump  log
	DEBUG,  // debug log

};

// sington logger class for log mannage
class Logger:noncopyable{
public:
	// get  only instance of logger
	static Logger& instance();
	// change log level that we want
	void setLogLevel(int level);  
	// writing log 
	void log(std::string msg);


private:
	int logLevel_;
	Logger(){;}
	Logger(const Logger &){;}
	Logger & operator=(const Logger){;} 



};