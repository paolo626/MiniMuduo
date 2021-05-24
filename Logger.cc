
#include<iostream>

#include "Logger.h"
#include "Timestamp.h"




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