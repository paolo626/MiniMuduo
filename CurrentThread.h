#pragma once

#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */


namespace CurrentThread{
	__thread int t_cachedTid ;

	void cacheTid();
	inline int tid(){
		if(__builtin_expect(t_cachedTid ==0 , 0)){  // the safe machine, dont need to understand.
			cacheTid();
		}
		return t_cachedTid;
	}

}