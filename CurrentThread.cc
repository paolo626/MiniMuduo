





#include "CurrentThread.h"

namespace CurrentThread{
	__thread int t_cachedTid ;  // define thread_local_var , same effective with thread_local of c++ key word.
	void cacheTid(){
		if(t_cachedTid ==0){
			t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));  // get current thread id. 
		}
	}
}