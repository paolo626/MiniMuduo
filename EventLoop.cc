



#include "EventLoop.h"

//  __thread is mean thread_local . only  has one  EventLoop in a pthread. but __thread make EventLoop is diff in pthread.
__thread EventLoop *t_loopInTHisThread = nullptr;  

