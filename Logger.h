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

// we use  define function make user using this logger class more easy 
// for user  just using  LOG_INFO define  is able to writing log 
#define  LOG_INFO(LogmsgFormat, ...)\
	do{\
		Logger & logger  = Logger::instance();\
		logger.setLogLevel(INFO);\
		char  buf[1024] = {0};\
		snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
		logger.log(buf);\
	}while(0)


#define  LOG_ERROR(LogmsgFormat,...)\
	do{\
		Logger & logger  = Logger::instance();\
		logger.setLogLevel(ERROR);\
		char  buf[1024] = {0};\
		snprintf(buf , 1024 , LogmsgFormat, ##__VA_ARGS);\
		logger.log(buf);\
	}while(0)


#define  LOG_FATAL(LogmsgFormat,...)\
	do{\
		Logger & logger  = Logger::instance();\
		logger.setLogLevel(FATAL);\
		char  buf[1024] = {0};\
		snprintf(buf , 1024 , LogmsgFormat, ##__VA_ARGS);\
		logger.log(buf);\
		exit(-1);\
	}while(0)

#ifdef MUDEBUG  // the debug log normally is closed status 
#define  LOG_DEBUG(LogmsgFormat,...)\
	do{\
		Logger & logger  = Logger::instance();\
		logger.setLogLevel(DEBUG);\
		char  buf[1024] = {0};\
		snprintf(buf , 1024 , LogmsgFormat, ##__VA_ARGS);\
		logger.log(buf);\
	}while(0)		
#else
	#define  LOG_DEBUG(LogmsgFormat,...)
#endif



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