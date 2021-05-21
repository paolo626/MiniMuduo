/************************************************

Copyright: SenseTime

Author: Chris Leo

Date:2021-01-09

Description:  there has two class for epoll manage.

channel  is used for all var in epoll ,  poller is  epoll's Encapsulation.

************************************************/
#pragma once 




#include<functional>
#include<atomic>
#include<vector>
#include<memory>
#include<mutex>



#include "noncopyable.h"
#include "Timestamp.h"
#include "CurrentThread.h"

class Channel;
class Poller;
 
class EvebtLoop:noncopyable{
public:
	using Functor = std::function<void()>;   // call back obj 
	
	// start event loop
	void loop();
	void quit();
	Timestamp pollReturnTime()const{return pollReturnTime_;}

	//  run the  fc obj   in current loop
	void runInLoop(Functor cb);
	//  run the  fc obj   in   another thread
	void queueInLoop(Functor cb);

	// wakeup the pthread which possess eventloop
	void wakeup();

	// encode epoller method in these  three fc 
	void updateChannel(Channel * channel);
	void removeChannel(Channel * channel);
	void hasChannel(Channel * channel);

	// whether  eventloop is in this pthread.
	bool isInLoopThread()const { return threadId_ == CurrentThread::tid();}
	

private:

	void hadnleRead();  // wake up 
	void doPengdingFunctors();  // do callback;

	using ChannelList  = std::vector<Channel *>;
	std::atomic_bool looping_;
	std::atomic_bool quit_; // quit loop 

	const pid_t threadId_;   //  mark id
	Timestamp  pollReturnTime_;  
	std::unique_ptr<Poller> poller_;
	
	int wakeupFd_;  // it is a mechism about wait/notify in multi-pthread.  when main loop get new fd channel, wakeupFd_ will used by eventfd to notice subloop to detail it.   
	std::unique_ptr<Channel> wakeChannel_;
	ChannelList activeChannels_;
	Channel * currentActiveChannel_;

	std::atomic_bool  callingPendingFunctors_;  // whether has call back;	
	std::vector<Functor> pendingFunctors_;  // save all callback that loop need to deal
	std::mutex mutex_;   // to provde safe about c++  contain, like vector  unique.








};