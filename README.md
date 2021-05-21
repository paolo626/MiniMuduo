# MiniMuduo
Here is a  mini version of muduo. it inspired by chengshuo 


# 编程问题

1. define 内容别的地方引用时候要在头文件里面define才能用到。 
2. logger.cc 中 LOG_INFO(LogmsgFormat, ...)\   ,号要注意空格。
3. 函数如果定义了变量要记得传入变量。 
4.  override 让编辑器去保证基类有个方法的虚函数。
5. 在c++里面  strcut a  可以省略 struct ,  a 就是这类型了。 
6. 如果只用类型防止语法报错，那么可以省略头文件，直接class 类名 做声明， 但是如果调用类的方法话， 必须包含头文件了。
7. 日志怎么加呢， 重要的接口需要加， 频繁调用的重要接口要设置启动级别高的日志，例如debug。 
8.  How to get address  of vector ?  &*myvector.begin();  , the *myvector.begin() get var , & get address.
9. 宏定义的内容必须严格遵循规则， 我多加了个空格都不行， 服了。 
10.  thread_local 在多线程设置不共享的变量，但是也不在代码段。 例如我们定义 thread_local 用来获取多线程的id， 虽然在全局位置 ，但是不共享。 


## 设计问题
1. 和tinywebsever 那个项目相比， 在多线程交互中muduo并没有采用中间quene+ 条件变量互斥锁做生产消费的通信设计， 而是用eventfd这个高级api放入epoll监听的fd中，做了工作线程的轮询唤醒。 工作线程唤醒起来的话从epoll_wait往下走， 执行回调任务。 这样会让代码看起来难懂， 看起来十分费劲。。。 但是很巧妙。
2. muduo库是框架， 所以设计时候不是面向过程思想，没有实际业务， 只是为了封装功能让其他人使用，所以理解为什么要这样做的时候， 没有实际的业务做支持难以理解。 不像tinywebsever就是为了实现一个功能，而不是封装成库。（不过也有一定的思想）


