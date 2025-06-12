#include "server.h"

int main(int agrc, const char *argv[]){

	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0){
	    perror("socket");
	    exit(EXIT_FAILURE);
	}
	//绑定
	struct sockaddr_in addr = {
	    .sin_family = AF_INET,
	    .sin_port = htons(PORT),
	    .sin_addr = {},
	};
	if( bind(fd, (struct sockaddr *)&addr, sizeof(addr) ) == -1){
	    perror("bind");
	    exit(EXIT_FAILURE);
	}

	//准备sqlite3数据库
	sqlite3 *db;
	FILE *fp = fopen(DBFILENAME, "r");
	if(fp == NULL){
	    init_lockers();
	}else{
	    fclose(fp);
	    printf("数据库和表 'parcels' 已经存在,无需创建。\n");
	}
	int rc = sqlite3_open(DBFILENAME, &db);
	if(rc != SQLITE_OK){
	    fprintf(stderr, "无法打开数据库:%s\n", sqlite3_errmsg(db));
	    sqlite3_close(db);
	    return -1;
	}

	//接收数据
	int ret;
	char buf[BUFSIZ] = {};
	struct sockaddr_in client_addr;
	socklen_t addrlen = sizeof(client_addr);
	while(1){
	    recvfrom(fd, buf, BUFSIZ, 0, (struct sockaddr *)&client_addr, &addrlen);
	    printf("recv data:[%c]%s\n", buf[0], buf+1);
	    
	    //识别消息类型,处理消息
	    switch(buf[0]){
	        case 'r': //注册消息
		    ret = do_register(&buf[1]);
		    //buf[0] = 0;
		    break;
		case 'l': //登录消息
		    ret = do_login(&buf[1]);
		    break;
		case 'p': //取件消息
		    ret = do_pickup(&buf[1]);
		    break;
		case 'd': //投递
		    ret = do_delivery(&buf[1]);
		    break;
		default:
		    fprintf(stderr, "不存在的消息类型:%c\n", buf[0]);
		    //break;
	    }
	    
	    sendto(fd, buf, strlen(&buf[1])+2, 0, (struct sockaddr *)&client_addr, addrlen);

	        
	}
	//关闭数据库连接
	sqlite3_close(db);
	//关闭套接字
	close(fd);
	return 0;
}
