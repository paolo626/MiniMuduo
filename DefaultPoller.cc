#pragma once 


#include "Poller.h"
#include <stdlib.h>


// it is good code style that   we dont add  develop calss head file in base calss achieve of Poller. 
Poller* Poller::hasChannel(EventLoop *Loop){
	if(::getenv("NUDUO_USE_POLL")){
		return nullptr;
	}
	else{
		return nullptr;
	}

}