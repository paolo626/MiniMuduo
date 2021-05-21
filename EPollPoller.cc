
#include <string.h>
#include <unistd.h>
#include<string.h>

#include "EPollPoller.h"
#include "Logger.h"
#include "Channel.h"
#include "Timestamp.h"

// the status of channel.

// channel is not add epoller
const int kNew = -1;
// had add into epoller
const int kAdded = 1;
// had delete
const int kDeleted = 2;


EPollPoller::EPollPoller(EventLoop *Loop)
: Poller(Loop),epollfd_(::epoll_create1(EPOLL_CLOEXEC)),events_(kInitEventListSize){ //when sub-process is fork , the derive fd from main-process will close.
	if(epollfd_ < 0){
		LOG_FATAL("epoll create error:%d \n", errno);
	}

}
EPollPoller::~EPollPoller(){
	::close(epollfd_);
}

// epoll wait
Timestamp EPollPoller::poll( int timeoutMs, ChannelList *activeChannels) {
	LOG_INFO("func = %s =>  fd total count = %lu  \n",__FUNCTION__ ,channels_.size());

	int numEvents = ::epoll_wait(epollfd_ , &*events_.begin(),static_cast<int>(events_.size()),timeoutMs);
	int saveErrno  = errno;  // errno is system var.  we save it in multi-pthread
	Timestamp now(Timestamp::now());

	if(numEvents > 0){
		LOG_INFO("event happend  \n");
		fillActiveChannels(numEvents, activeChannels);
		if(numEvents ==events_.size()){
			events_.resize(events_.size()*2);  // because muduo used LT  so we just resize double size and not deal in this loop , the event will happened again in the next time.
		} 
			
	}
	else if(numEvents ==0){     
		LOG_DEBUG("func = %s time out \n",__FUNCTION__ );
	}
	
	else{
		if(saveErrno != EINTR){  // 
			errno = saveErrno;  // it avoid  multi-pthread confliect.
			LOG_ERROR("EPollPoller::poll() error");

		}
	}

	return now;
}
	


void EPollPoller::fillActiveChannels(int numEvents , ChannelList *activeChannels) const{
	for( int i = 0 ; i<numEvents; ++i){
		Channel * channel = static_cast<Channel *>(events_[i].data.ptr);     //static_cast  make the void *  of data.ptr  to channel *
		channel->set_revents(events_[i].events);
		activeChannels->push_back(channel);    // the event actived by epoller will give ChannelList . it will been used by EventLoop
	}
	
}


// channel update remove is call by EventLoop updateChannel removeChannel(it ecode epoller updateChannel removeChannel  )
// we need to know channel is not has relationship with epoll.
void EPollPoller::updateChannel(Channel *channel){
	const int index = channel->index();
	LOG_INFO("func = %s => fd = %d , events = %d index = %d \n",__FUNCTION__ ,channel->fd(), channel->events(),index);
	if(index ==kNew || index ==kDeleted){
		if(index ==kNew){
			int fd = channel->fd();
			channel->set_index(kAdded);
			update(EPOLL_CTL_ADD,channel);
		}
		else{    //already add
			int fd = channel->fd();
			if(channel->isNoneEvent()){
				update(EPOLL_CTL_DEL, channel);
			}
			else{
				update(EPOLL_CTL_MOD, channel);
			}

		}
	}


}


void EPollPoller::update(int operation , Channel *channel){
	struct epoll_event event;
	bzero(&event,  sizeof(event));
	event.events = channel->events(); // interest event register.
	int fd = channel->fd();
	event.data.fd = fd;
	event.data.ptr = channel; // save channel into systrem event.

	if(::epoll_ctl(epollfd_, operation, fd, &event) < 0){
		if(operation == EPOLL_CTL_DEL){
			LOG_ERROR("epoll_ctl del error : %d\n",errno); 
		}
		else{
			LOG_FATAL("epoll_ctl add or mod error : %d\n",errno); 

		}
	}
}
//delete channel from epoller
void EPollPoller::removeChannel(Channel * channel){
	int fd = channel->fd();
	channels_.erase(fd);
	LOG_INFO("func = %s => fd = %d  \n",__FUNCTION__ ,fd);

	int index = channel->index();
	if(index ==kAdded){
		update(EPOLL_CTL_DEL, channel); 
	}
	channel->set_index(kNew);

};

