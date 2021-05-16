

#include "InetAddress.h"
#include <strings.h>
#include <string.h>


InetAddress::InetAddress(uint16_t port , std::string ip){  // define is not need default parm , but declare  need 



	bzero(&addr_, sizeof addr_);
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port);   // network squence 
	addr_.sin_addr.s_addr =  inet_addr(ip.c_str());


}
std::string  InetAddress::toIp()const{
	char buf[64]  = {0};
	::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
	return buf;   // this may be auto char to string 

}
std::string InetAddress::toIpPort()const{
	char buf[64]  = {0};
	::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
	size_t end = strlen(buf);
	uint16_t port = ntohs(addr_.sin_port);
	sprintf(buf+end,":%u", port);  // consist  ip and port 
	return buf;   


}
uint16_t InetAddress::toPort() const {
	return ntohs(addr_.sin_port);
}


//#define TIMETEST
#ifdef TIMETEST
#include<iostream>
int main(){
	InetAddress addr(8080, "127.0.0.1");
	std::cout<<addr.toIpPort()<<std::endl;
	return 0;

}
#endif