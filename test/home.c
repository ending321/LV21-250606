#include <stdio.h>
#include<string.h>
#include<sqlite3.h>
#include<stdlib.h>

#define DBFILENAME "lockers.db"

void print_head();
void print_body();
void print_footer();

void set_status();
void set_couriers();
void set_records();

int main() {
    print_head();
    print_body();
    print_footer();
    return 0;
}
void print_head(){
    printf("Content-Type: text/html\n\n");
    printf("<!DOCTYPE html>\n");
    printf("<html lang=\"zh\">\n");
    printf("<head>\n");
    printf("    <meta charset=\"UTF-8\">\n");
    printf("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
    printf("    <title>快递柜管理</title>\n");
    printf("    <link rel=\"stylesheet\" href=\"/styles.css\">\n");
    printf("</head>\n");
    printf("<body>\n");

}
void print_body(){
    printf("<div id=\"header\">\n");
    printf("  <h1>快递柜管理员后台</h1>\n");
    printf("</div>\n");

    set_status();

    printf("</div>\n");
    printf("<div>\n");
    printf("   <table>\n");
    printf("  <thead>\n");
    printf("    <tr>\n");
    printf("      <th colspan=\"9\">投递记录</th>\n");
    printf("    </tr>\n");
    printf("    <tr>\n");
    printf("      <th>记录编号</th>\n");
    printf("      <th>快递包裹号</th>\n");
    printf("      <th>快递员手机号</th>\n");
    printf("      <th>快递公司</th>\n");
    printf("      <th>投递时间</th>\n");
    printf("      <th>收件人手机号</th>\n");
    printf("      <th>取件码</th>\n");
    printf("      <th>取件时间</th>\n");
    printf("      <th>取件方式</th>\n");
    printf("    </tr>\n");
    printf("  </thead>\n");
    printf("    <tbody>\n");
    set_records();
    printf("    </tbody>\n");
    printf("  </table>\n");
    printf("</div>\n");
    printf("<div>\n");
    printf("   <table>\n");
    printf("  <thead>\n");
    printf("    <tr>\n");
    printf("      <th colspan=\"4\">快递员信息</th>\n");
    printf("    </tr>\n");
    printf("    <tr>\n");
    printf("      <th>ID</th>\n");
    printf("      <th>手机号</th>\n");
    printf("      <th>密码</th>\n");
    printf("      <th>公司</th>\n");
    printf("    </tr>\n");
    printf("  </thead>\n");
    set_couriers();
    printf("    </tbody>\n");
    printf("  </table>\n");
    printf("</div>\n");
}

void print_footer(){
    printf("</body>\n");
    printf("</html>\n");
}

void set_status(){
    sqlite3 *db;
    //打开数据库
    int rc = sqlite3_open(DBFILENAME, &db);
    if(rc != SQLITE_OK){
        perror("无法打开数据库");
	exit(EXIT_FAILURE);
    }

    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM lockers";
    //准备SQL语句
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        perror("无法准备SQL语句");
	sqlite3_close(db);
	exit(EXIT_FAILURE);
    }
    
    int i = -1;
    char values[20][50] = {};
    char status[20][50] = {};
    while(sqlite3_step(stmt) == SQLITE_ROW && ++i < 20){
	strcpy(status[i], (const char *)sqlite3_column_text(stmt, 1));
	if(strncmp(status[i], "占用", strlen("占用")) == 0){
	    strcpy(values[i], "status-occupied");
	}else if(strncmp(status[i], "使用中", strlen("使用中")) == 0){
	    strcpy(values[i], "status-use");
	}else if(strncmp(status[i], "空闲", strlen("空闲")) == 0){
	    strcpy(values[i], "status-free");
	}else if(strncmp(status[i], "故障", strlen("故障")) == 0){
	    strcpy(values[i], "status-damaged");
	}else{
	    strcpy(values[i], "status-err");
	}
	//printf("%s-----%s\n", values[i], status [i]);
    }
    if(rc != SQLITE_ROW && i<19){
        perror("查询失败");
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	exit(EXIT_FAILURE);
    }
    
    printf("<div>\n");
    printf("    <table id=\"status\">\n");
    printf("        <tbody>\n");
    printf("            <th colspan=\"3\">快递柜状态</th>\n");

    printf("	<tr class=\"large\">\n");
    printf("	  <td class=\"%s\">01 %s</td>\n", values[0], status[0]);
    printf("	  <td rowspan=\"10\" id=\"wireway\"></td>\n");
    printf("	  <td class=\"%s\">11 %s</td> </tr>\n", values[10], status[10]);

    char *size[9] = {"medium", "small", "small", "small", "small", "small", "medium", "medium", "medium"};
    
    for(i=0; i<9; i++){
        printf("	<tr class=\"%s\">\n", size[i]);
	printf("	  <td class=\"%s\">%02d %s</td>\n", values[i+1], i+2, status[i+1]);
        printf("	  <td class=\"%s\">%02d %s</td> </tr>\n", values[i+11], i+12, status[i+11]);
    }
    printf("            <tr>\n");
    printf("                <td colspan=\"3\"></td>\n");
    printf("            </tr>\n");
    printf("        </tbody>\n");
    printf("    </table>\n");
    printf("</div>\n");

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void set_records(){

    //打开数据库连接
    sqlite3 *db;
    int rc = sqlite3_open(DBFILENAME, &db);
    if(rc != SQLITE_OK){
	perror("set_couriers无法打开数据库");
	exit(EXIT_FAILURE);
    }

    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM records";
    //准备SQL语句
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        perror("无法准备SQL语句");
	sqlite3_close(db);
	exit(EXIT_FAILURE);
    }
    while(sqlite3_step(stmt) == SQLITE_ROW){
        printf("    <tr>\n");
	for(int i=0; i<9; i++){
	    char *value = (char *)sqlite3_column_text(stmt, i);
	    printf("<td>%s</td>", value == NULL ? "-" : value);
	}
	printf("    </tr>\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void set_couriers(){

    //打开数据库连接
    sqlite3 *db;
    int rc = sqlite3_open(DBFILENAME, &db);
    if(rc != SQLITE_OK){
	fprintf(stderr, "无法打开数据库: %s\n", sqlite3_errmsg(db));
	exit(EXIT_FAILURE);
    }

    sqlite3_stmt *stmt;
    char *sql = "SELECT * FROM couriers";
    //准备SQL语句
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	fprintf(stderr, "无法准备SQL语句:%s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	exit(EXIT_FAILURE);
    }

    while(sqlite3_step(stmt) == SQLITE_ROW){
        printf("    <tr>\n");
	for (int i=0; i<4; i++){
	    char *value = (char *)sqlite3_column_text(stmt, i);
	    printf("<td>%s</td>", value);
	}
	printf("    </tr>\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
