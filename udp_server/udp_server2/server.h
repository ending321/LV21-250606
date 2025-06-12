#ifndef SERVER_H
#define SERVER_H
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/udp.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/types.h>

//定义消息类型
enum TypeProtocol{
	PROTOCOL_TYPE_NONE,
	PROTOCOL_TYPE_REGISTER, //注册消息
	PROTOCOL_TYPE_LOGIN,   //登录消息
	PROTOCOL_TYPE_PICKUP,  //取件消息
	PROTOCOL_TYPE_DELIVERY //投递
};

#define ErrExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define PORT 8888
#define DBFILENAME "lockers.db"

int init_lockers();
int do_register(char *buf);
int do_login(char *buf);
int do_pickup(char *buf);
int do_delivery(char *buf);

#endif
