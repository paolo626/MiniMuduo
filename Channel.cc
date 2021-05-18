

#include<sys/epoll.h>

#include "Channel.h"



const int Channel::kNoneEvent = 0 ;
const int Channel::kReadEvent  = EPOLLIN|EPOLLPRI;
const int Channel::kWriteEvent  = EPOLLOUT;


Channel::Channel(EventLoop* Loop, int fd)
	:loop_(Loop),fd_(fd),events_(0),revents_(0),index_(-1),tied_(false){
		;

}
~Channel::Channel(){
	
}


// weak for dection.
void Channel::tie(const std::shared_ptr<void> &  obj){
	 tie_ = obj;
	 tied_ = true;

}
