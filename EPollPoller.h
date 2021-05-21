#pragma once 
#include <vector>
#include <sys/epoll.h>

#include "Poller.h"


/**
 * let me revoke how to use epoll by system api
 * epoll_create 
 * epoll_ctl  add/mod/del
 * epoll_wait   
 *  we just move these api  into EPollPoller class fc;
 * */
class EPollPoller: public Poller{
public :
	EPollPoller(EventLoop *Loop);
	~EPollPoller() override;

	// re-writing   fc of virtual
	Timestamp poll( int timeoutMs, ChannelList *activeChannels) override;
	void updateChannel(Channel *channel)override;
	void removeChannel(Channel * channel)override;


private:
	static const int kInitEventListSize = 16; // init vector size
	//fill active channel;
	void fillActiveChannels(int numEvents , ChannelList *activeChannels) const;
	// update channel events.
	void update(int operation , Channel *channel);




	using EventList = std::vector<epoll_event>;
	int epollfd_;
	EventList events_;

};