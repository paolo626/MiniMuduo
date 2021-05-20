# MiniMuduo
Here is a  mini version of muduo. it inspired by chengshuo 


# 问题

1. define 内容别的地方引用时候要在头文件里面define才能用到。 
2. logger.cc 中 LOG_INFO(LogmsgFormat, ...)\   ,号要注意空格。
3. 函数如果定义了变量要记得传入变量。 
4.  override 让编辑器去保证基类有个方法的虚函数。
5. 在c++里面  strcut a  可以省略 struct ,  a 就是这类型了。 
6. 如果只用类型防止语法报错，那么可以省略头文件，直接class 类名 做声明， 但是如果调用类的方法话， 必须包含头文件了。
7. 日志怎么加呢， 重要的接口需要加， 频繁调用的重要接口要设置启动级别高的日志，例如debug。 