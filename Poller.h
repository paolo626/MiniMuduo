/************************************************

Copyright: SenseTime

Author: Chris Leo

Date:2021-01-09

Description:   poller calss help we using epoll easily.

************************************************/

#pragma once
#include<vector>
#include<unordered_map>


#inlcude "TimeStap.h"
class Channel;
class EventLoop;

class Poller{

public:
	using ChannelList = std::vector<Channel*> ;
	Poller(EventLoop* Loop);
	virtual ~Poller();

	//  the fc for io multi-use.
	virtual Timestamp poll (int timeoutMs, ChannelList *activeChannels) = 0;
	virtual void updateChannel(Channel *channel) = 0;  // epoll ctrl
	virtual void removeChannel(Channel * channel) = 0; // epoll ctrl
	virtual bool hasChannel(Channel * channel ) const ; // whether channel is in this poller


	// singleton to get instance from base class.
	static Poller newDefaultPoller(EventLoop *Loop);


protected:
    // socket fd is int ,   Channel* is class contain fd.
	using ChannelMap = std::unordered_map<int , Channel*>; 
	ChannelMap channels_;

	

private:
	EventLoop * ownerLoop_;
};