
#include<iostream>

#include "Logger.h"
#include "Timestamp.h"


// we use  define function make user using this logger class more easy 
// for user  just using  LOG_INFO define  is able to writing log 
#define  LOG_INFO(LogmsgFormat,...)\
	do{\
		Logger & logger  = Logger::instance();\
		logger.setLogLevel(INFO);\
		char  buf[1024] = {0};\
		snprintf(buf , 1024 , LogmsgFormat, ##__VA_ARGS);\
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


Logger& Logger::instance(){
	 static  Logger  logger;  // pthreat safe 
	 return logger;

}
	// change log level that we want
void Logger::setLogLevel(int level){
	logLevel_ = level;
}
	// writing log 
void Logger::log(std::string msg){
	switch(logLevel_){
		case INFO:
			std::cout<<"INFO:";
			break;
		case ERROR:
			std::cout<<"ERROR:";
			break;
		case FATAL:
			std::cout<<"FATAL:";
			break;
		case DEBUG:
			std::cout<<"DEBUG:";
			break;									
	}
	std::cout<<"Time: "<<Timestamp::now().toString()<<" : "<<msg<<std::endl;   // this can been replace by file in the normal work. 

}