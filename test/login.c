#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USERNAME "admin"
#define PASSWD "123"

int main(int argc, char *argv[]){

	//获取收到的数据
	char *data = getenv("QUERY_STRING");
	char username[50], password[50];
	sscanf(data, "username=%49[^&]&password=%49s", username, password);
	printf("Content-Type: text/html\n\n");
	printf("<html>");
	printf("<head>");
	printf("<meta charset=\"UTF-8\">");
	printf("</head>");
	printf("<body>");
	if(strncmp(username, USERNAME, 49) || strncmp(password, PASSWD, 49)){
	    printf("<h3>用户名或者密码错误</h3>");
	    printf("<meta http-equiv=\"refresh\" content=\"1; url=/index.html\">");
	}else{
	    printf("<h3>登录成功! Welcome, %s!</h3>", username);
	    printf("<meta http-equiv=\"refresh\" content=\"1; url=/cgi-bin/home.cgi\">");
	}
	printf("</body>");
	printf("</html>");
	//printf("<h1>Login successful! Welcome, %s!</h1>", username);

	return 0;
}
