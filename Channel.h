/************************************************

Copyright: SenseTime

Author: Chris Leo

Date:2021-01-09

Description:  

channel  is used for all sockets ,   and the event of epollin or epollout.

************************************************/


#pragma once 

#include<functional>
#include<memory>

#include "noncopyable.h"
#include "Timestamp.h"

class EventLoop ;



class Channel:noncopyable{

public:
	using EventCallback = std::function<void()>;  
	// function is a object  that it ()operator  pointer void(TimeStamp), so we can save this function eveywhere.
	// using is another name of std::function<void(TimeStamp)>. 
	using ReadEventCallBack = std::function<void(Timestamp)>;
	Channel(EventLoop* loop, int fd);  // this is pointer ,so it used just declare.
	~Channel();
	void handleEvent(Timestamp receiveTime);


private:
	static const int  kNoneEvent;
	static const int  kReadEvent;
	static const int  kWriteEvent;
	EventLoop * loop_;
	const int fd;   // the fd of socket 
	int events_;   // register event
	int revents_;  // revoke event 
	int index_;
	std::weak_ptr<void> tie_;
	bool tied_;

	// channel can get revoke event  in revents_ , so we define callback for revoke used. 
	ReadEventCallBack readCallback_;
	EventCallback  writeCallback_;
	EventCallback  closeCallback_;
	EventCallback  errorCallback_;



};