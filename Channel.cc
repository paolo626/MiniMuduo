

#include<sys/epoll.h>

#include "Channel.h"
#include "Logger.h"



const int Channel::kNoneEvent = 0 ;
const int Channel::kReadEvent  = EPOLLIN|EPOLLPRI;
const int Channel::kWriteEvent  = EPOLLOUT;


Channel::Channel(EventLoop* Loop, int fd) //EventLoop contain epoller, channnel.
	:loop_(Loop),fd_(fd),events_(0),revents_(0),index_(-1),tied_(false){
		;

}
Channel::~Channel(){

	
}


// weak for dection. it will used by 
void Channel::tie(const std::shared_ptr<void> &  obj){
	 tie_ = obj;
	 tied_ = true;

}
// when channel fd  is change , using update() to change poller's fd by  eventloop
void Channel::update(){
	// add code 

}

//  delete channel  in eventloop
void Channel::remove(){
   //add code 
}


// deal events from  epoller to notice  and using call back  in deal.
void Channel::handleEventWithGuard(Timestamp reveiveTime){
	LOG_INFO("channel handlevent revents: %d",revents_);
	if((revents_ & EPOLLHUP) && !(revents_&EPOLLIN)){
		if(closeCallback_)closeCallback_();
	}
	if(revents_ &EPOLLERR){
		if(errorCallback_)errorCallback_();
	}
	if(revents_ & (EPOLLIN|EPOLLPRI)){
		if(readCallback_)readCallback_(reveiveTime);
	}
	if(revents_ & EPOLLOUT){
		if(writeCallback_)writeCallback_();
	}

}


void  Channel::handleEvent(Timestamp receiveTime){
	
	if(tied_){
		std::shared_ptr<void>guard = tie_.lock();
		if(guard){
			handleEventWithGuard(receiveTime);
		}

	}
	else{
		handleEventWithGuard(receiveTime);
	}
}

