/************************************************

Copyright: SenseTime

Author: Chris Leo

Date:2021-01-09

Description:   this is class for manange time 

************************************************/
#pragma once 

#include<iostream>
#include<string>

class Timestamp{
public:
	Timestamp();
	explicit   Timestamp(int64_t microSecondsSinceEpoch_);
	static  Timestamp now();
	std::string toString()const ;


private:
	int64_t microSecondsSinceEpoch_;
};
