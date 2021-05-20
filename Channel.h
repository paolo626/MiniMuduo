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


 // we have many pthread.  every pthread has one poller, every poller has many channel. one channel only belong one loop.
class Channel:noncopyable{

public:
	using EventCallback = std::function<void()>;  
	// function is a object  that it ()operator  pointer void(TimeStamp), so we can save this function eveywhere.
	// using is another name of std::function<void(TimeStamp)>. 
	using ReadEventCallback = std::function<void(Timestamp)>;

	Channel(EventLoop* Loop, int fd);  // this is pointer ,so it used just declare.
	~Channel();
	// this is callback fc that the fc  will register by other std::function<void()>; 
	//  when epoller want to notices fd, it will be used.
	void handleEvent(Timestamp receiveTime);

	// define callback object  ,we make another fc object move to channel local var; 
	void setReadCallback(ReadEventCallback cb){	readCallback_ = std::move(cb); }

	void setWriteCallback(EventCallback cb){writeCallback_ = std::move(cb); }	

	void setCloseCallback(EventCallback cb){closeCallback_ = std::move(cb); }	
	void setErrorCallback(EventCallback cb){errorCallback_ = std::move(cb); }	

	//  this using weak to detective that   shared pointer is alive. make sure that channel is onwork
	void tie(const std::shared_ptr<void> &);

	int fd()const {return fd_;}
	int events()const {return events_;}
	int set_revents(int revt){revents_ = revt;}// used by epoller. 
	bool isNoneEvent()const {return events_ ==kNoneEvent;}
	bool isWriting()const {return events_ ==kWriteEvent;}
	bool isReading() const {return events_ ==kReadEvent;}
	// set fd staues.
	 // update is epoller cntl to reset fd event.
	void enableReading(){events_ |=kReadEvent; update();}
	void disableReading(){events_ &=~kReadEvent; update();}
	void enableWriting(){events_ |=kWriteEvent; update();}
	void disableWriting(){events_ &=~kWriteEvent; update();}	
	void disableAll(){events_ |=kNoneEvent; update();}


	int index(){ return index_;}

	void set_index(int idx){index_ = idx; } 
	EventLoop* ownerLoop(){ return loop_;}
	void remove();


	



private:
	void update();
	void handleEventWithGuard(Timestamp receiveTime);
	static const int  kNoneEvent;
	static const int  kReadEvent;
	static const int  kWriteEvent;
	EventLoop * loop_;
	const int fd_;   // the fd of socket 
	int events_;   // register event
	int revents_;  // revoke event 
	int index_;

	std::weak_ptr<void> tie_;
	bool tied_;

	// channel can get revoke event  in revents_ , so we define callback for revoke used. 
	// these four callback is define by user, just using in this.
	ReadEventCallback readCallback_;
	
	EventCallback  writeCallback_;
	EventCallback  closeCallback_;
	EventCallback  errorCallback_;



};