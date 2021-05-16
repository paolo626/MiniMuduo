/************************************************

Copyright: SenseTime

Author: Chris Leo

Date:2021-01-09

Description: this is class that make our inheritance class 
is not able copy , and just able to create one. this is a code style.   

************************************************/

#pragma once 

class noncopyable{
public:
	noncopyable(const noncopyable &) = delete;
	noncopyable&  operator=(const noncopyable &) = delete;

protected:
	noncopyable() = default;
	~noncopyable() = default;

};