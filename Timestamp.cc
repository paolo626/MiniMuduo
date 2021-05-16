
#include "Timestamp.h"

Timestamp::Timestamp():microSecondsSinceEpoch_(0){}

//explicit is able avoid int char var is become calss by copy function.  this cases some unrelize error  
Timestamp::Timestamp(int64_t microSecondsSinceEpoch_)
    :microSecondsSinceEpoch_(microSecondsSinceEpoch_){


}
Timestamp Timestamp::now(){  // this is static fc,so we dont need creat class at begin
	time_t  ti  = time(NULL);
	return  Timestamp(ti);

}
std::string Timestamp::toString()const {
	char buf[128]  = {0};
	tm* tm_time = localtime(&microSecondsSinceEpoch_);
	snprintf(buf,128, "%4d/%02d/%02d/%02d:%02d:%02d",
	tm_time->tm_year+1900,
	tm_time->tm_mon +1,
	tm_time->tm_mday,
	tm_time->tm_hour,
	tm_time->tm_min,
	tm_time->tm_sec);
	return buf;
}

//#define TIMETEST
#ifdef TIMETEST
#include<iostream>
int main(){
	std::cout<<Timestamp::now().toString()<<std::endl;
	return 0;

}
#endif