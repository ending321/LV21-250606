#include"server.h"

struct {
	char number[32];
	char company[32];
}courier;

int init_lockers() {
	sqlite3 *db;
	char *err_msg = 0;
	//FILE *fp = fopen(DBFILENAME, "r");
	int rc;
	const char *sql;

	rc = sqlite3_open(DBFILENAME, &db);
	if(rc != SQLITE_OK){
	    fprintf(stderr, "无法打开数据库:%s\n",sqlite3_errmsg(db));
	    sqlite3_close(db);
	    return -1;
	}

	//执行创建表的SQL语句
	sql = "CREATE TABLE lockers ("
		"id INTEGER PRIMARY KEY,"  //柜子编号
		"status TEXT CHECK(status IN ('占用', '使用中', '空闲')) NOT NULL," //柜子状态
		"size TEXT CHECK(size IN ('大', '中', '小')) NOT NULL,"           //柜子的尺寸
		"package_no TEXT,"         //包裹号
		"courier_phone TEXT,"      //快递员手机号
		"delivery_company TEXT,"   //快递公司信息
		"delivery_time TEXT,"      //投递时间
		"recipient_phone TEXT,"     //收件人手机号
		"pickup_code TEXT"
		");";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if(rc != SQLITE_OK){
	    fprintf(stderr, "创建表失败: %s\n", err_msg);
	    sqlite3_free(err_msg);
	}else{
	    printf("表 'parcels' 创建成功\n");
	}

	//启动事务
	sql = "BEGIN TRANSACTION;";
	sqlite3_exec(db, sql, 0, 0, &err_msg);

	//插入数据
	for (int i = 1; i < 21; i++) {
	    switch(i) {
		case 1:
		case 11:
		    sql = "INSERT INTO lockers (status, size) VALUES ('空闲', '大');";
		    break;
		case 2:
		    sql = "INSERT INTO lockers (status, size) VALUES ('空闲', '中');";
		    break;
		case 12:
		    sql = "INSERT INTO lockers (status, size) VALUES ('占用', '中');";  //显示屏占用
		    break;
		case 8:
		case 9:
		case 10:
		case 18:
		case 19:
		case 20:
		    sql = "INSERT INTO lockers (status, size) VALUES ('空闲', '中');";
		    break;
		default:
		    sql = "INSERT INTO lockers (status, size) VALUES ('空闲', '小');";
	    }
	    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	    if (rc != SQLITE_OK) {
		fprintf(stderr, "插入数据失败: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_exec(db, "ROLLBACK:", NULL, NULL, &err_msg);
		sqlite3_close(db);
		return 1;
	    }
	}

	//提交事务
	sql = "COMMIT;";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if (rc != SQLITE_OK) {
	    fprintf(stderr, "事务提交失败: %s\n", err_msg);
	    sqlite3_free(err_msg);
	}else{
	    printf("成功插入了20条记录\n");
	}
	//创建快递员登记表
	sql = "CREATE TABLE couriers ("
		"id INTEGER PRIMARY KEY,"
		"courier_phone TEXT UNIQUE,"
		"password TEXT,"
		"delivery_company TEXT"
		");";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if(rc != SQLITE_OK){
	    fprintf(stderr, "创建快递员登记表 失败: %s\n", err_msg);
	    sqlite3_free(err_msg);
	    sqlite3_close(db);
	    exit(EXIT_FAILURE);
	}

	//创建投递记录表
	sql = "CREATE TABLE records ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"     //记录编号
		"package_no TEXT,"         //包裹号
		"courier_phone TEXT,"      //快递员手机号
		"delivery_company TEXT,"   //快递公司信息
		"delivery_time TEXT,"      //投递时间
		"recipient_phone TEXT,"    //收件人手机号
		"pickup_code TEXT,"        //取件码 
		"pickup_time TEXT,"        //取件时间
		"pickup_method TEXT CHECK(pickup_method IN ('快递员回收', '管理员开柜', '取件码取件'))"
		");";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if(rc != SQLITE_OK){
	    fprintf(stderr, "创建投递记录表 失败: %s\n", err_msg);
	    sqlite3_free(err_msg);
	    sqlite3_close(db);
	    exit(EXIT_FAILURE);
	}

	//触发器
	sql = "CREATE TRIGGER update_recordss "
		"AFTER UPDATE ON lockers "
		"FOR EACH ROW "
		"BEGIN "
		" INSERT INTO records (package_no, courier_phone, delivery_company, delivery_time, recipient_phone, pickup_code) "
		" SELECT NEW.package_no, NEW.courier_phone, NEW.delivery_company, NEW.delivery_time, NEW.recipient_phone, NEW.pickup_code "
		"WHERE NEW.package_no IS NOT NULL;"
		"END;";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if(rc != SQLITE_OK){
	    fprintf(stderr, "触发器update_records创建 失败: %s\n", err_msg);
	    sqlite3_free(err_msg);
	    sqlite3_close(db);
	    exit(EXIT_FAILURE);
	}
	
	sql = "CREATE TRIGGER update_lockers"
		"AFTER UPDATE OF pickup_code, pickup_method ON records "
		"FOR EACH ROW "
		"BEGIN "
		"UPDATE lockers SET "
		"package_no = NULL, "
		"courier_phone = NULL, "
		"delivery_company = NULL, "
		" delivery_time = NULL, "
		"recipient_phone = NULL, "
		"pickup_code = NULL, "
		"status = '空闲' "
		"WHERE lockers.package_no = OLD.package_no;"
		"END;";
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
	if(rc != SQLITE_OK){
	    fprintf(stderr, "触发器update_lockers创建 失败: %s\n", err_msg);
	    sqlite3_free(err_msg);
	    sqlite3_close(db);
	    exit(EXIT_FAILURE);
	}
	//关闭数据库连接
	sqlite3_close(db);
	return 0;
}

int do_register(char *buf){
	char *number = buf;
	char *passwd = buf + strlen(buf)+1;
	char *company = passwd + strlen(passwd)+1;
	printf("number:%s\n", number);
	printf("passwd:%s\n", passwd);
	printf("company:%s\n", company);
	sqlite3 *db;
	int rc = sqlite3_open(DBFILENAME, &db);
	if(rc != SQLITE_OK){
	    perror("do_register:sqlite3_open");
	    exit(EXIT_FAILURE);
	}

	//准备sql语句
#if 0
	char str[500] = {};
	sprintf(str, "INSERT_INTO couriers (courier phone, password, delivery_company) VALUES('%s', %s, '%s');", number, passwd, company);
#endif
	//占位符? 防止SQL注入
	char *sql =  "INSERT INTO couriers (courier_phone, password, delivery_company)"
		"VALUES (?,?,?);";
	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK){
	    perror("sqlite3_prepare_v2(db, sql, -1, &stmt, 0)");
	    sqlite3_close(db);
	    exit(EXIT_FAILURE);
	}
	sqlite3_bind_text(stmt, 1, number, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, passwd, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, company, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if(rc != SQLITE_DONE){
	    perror("sqlite3_step(stmt)");
	    sqlite3_close(db);
	    strcpy(buf, "注册失败，手机号已注册");
	    //清理statement 防止内存泄漏
	    sqlite3_finalize(stmt);
	    return -1;
	}
	//printf("sql:%s\n", sql);
	//清理statement 防止内存泄漏
	sqlite3_finalize(stmt);
	strcpy(buf, "ok");
	return 0;
}
int do_login(char *buf){
	char *number = buf;
	char *passwd = buf + strlen(buf)+1;	
	printf("number:%s\n", number);
	printf("passwd:%s\n", passwd);

	sqlite3 *db;
	int rc = sqlite3_open(DBFILENAME, &db);
	if(rc != SQLITE_OK){
	    perror("do_register");
	    exit(EXIT_FAILURE);
	}
	char *sql = "SELECT * FROM couriers WHERE courier_phone =? AND password = ?;";
	sqlite3_stmt *stmt;
	if(sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK){
	    perror("do_login:sqlite3_prepare_v2");
	    sqlite3_close(db);
	    exit(EXIT_FAILURE);
	}
	sqlite3_bind_text(stmt, 1, number, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, passwd, -1, SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	if(rc != SQLITE_ROW){
	    perror("do_login:sqlite3_step(stmt)");
	    sqlite3_close(db);
	    fprintf(stderr, "登录失败,手机号或密码不正确");
	    //清理statement防止内存泄漏
	    sqlite3_finalize(stmt);
	    return -1;
	}
	strcpy(courier.number, number);
	strcpy(courier.company, (char *)sqlite3_column_text(stmt, 3) );
	printf("登录成功，快递员属于%s\n", courier.company);
	//清理statement防止内存泄漏	
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	strcpy(buf, "ok");
	return 0;
}
int do_pickup(char *buf){
	//查询取件码是否正确
	sqlite3 *db;
	char *pickup_code = buf;
	//打开数据库
	int rc = sqlite3_open(DBFILENAME, &db);
	if(rc != SQLITE_OK){
	    perror("无法打开数据库");
	    sqlite3_close(db);
	    strcpy(buf+1, "数据库文件打开失败");
	    return -1;
	}
	sqlite3_stmt *stmt;
	char *sql = "SELECT * FROM lockers WHERE pickup_code = ? ";
	if(sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK){
	    perror("查询语句错误");
	    sqlite3_close(db);
	    strcpy(buf+1, "查询语句失败");
	    return -1;
	}
	//绑定参数, SQLITE_TRANSIENT表示让SQLite3在内部为pickup_code创建一个副本
	sqlite3_bind_text(stmt, 1, pickup_code, -1, SQLITE_TRANSIENT);
	rc = sqlite3_step(stmt);
	if(rc != SQLITE_ROW){
	    perror("bind_text查询失败");
	    sqlite3_close(db);
	    strcpy(buf+1, "bind_text失败");
	    return -1;
	}
	int locker_id = sqlite3_column_int(stmt, 0);
	printf("查询到的柜子编号为%d 是取件码 %s 的快递\n", locker_id, pickup_code);
	sqlite3_finalize(stmt);

	//取快递
	sql = sqlite3_mprintf("UPDATE records SET pickup_method = '取件码取件', "
			"pickup_time = datetime('now', 'localtime') " 
		 	"WHERE pickup_code = %Q", pickup_code);
	char *errMsg = NULL;
	rc  = sqlite3_exec(db, sql, 0, 0, &errMsg);
	if(rc != SQLITE_OK){
	    sprintf(buf, "取件失败: %s", errMsg);
	    printf("%s\n", buf);
	    sqlite3_free(errMsg);
	    sqlite3_free(sql);
	    return -1;
	}
	printf("包裹提取成功 柜子编号: %d\n", locker_id);
	/*
	char *number = buf;
	char *passwd = buf + strlen(buf)+1;
	char *company = passwd + strlen(passwd)+1;
	printf("number:%s\n", number);
	printf("passwd:%s\n", passwd);
	printf("company:%s\n", company);
	strcpy(buf, "ok");
	*/
	sqlite3_free(errMsg);
	sqlite3_free(sql);
	sprintf(buf, "%d", locker_id);
	sqlite3_close(db);
	return 0;
}
int do_delivery(char *buf){
	sqlite3 *db;
	int rc = 0;
	//int ret = 0;
	sqlite3_stmt *stmt;

	char *courier_number = buf + 1;//包裹号
	char *recipient_phone = courier_number + strlen(courier_number) + 1; //手机号

	const char *sizeText;
	switch(buf[0]){
	    case '0': sizeText = "小"; break;
	    case '1': sizeText = "中"; break;
	    case '2': sizeText = "大"; break;
	    default: 
		printf("无效的大小参数。\n");
		strcpy(buf+1, "无效的大小参数。");
		return -1;
	}
	printf("[%s]快递单号：%s, 收件人手机号：%s\n", sizeText, courier_number, recipient_phone);

	//打开数据库连接
	rc = sqlite3_open(DBFILENAME, &db);
	if(rc!=SQLITE_OK){
	    perror("do_delivery:sqlite3_open");
	    sqlite3_close(db);
	    strcpy(buf+1, "数据库文件打开失败");
	    return -1;
	}

	//查找一个空闲的柜子，其尺寸符合需要投递的快递尺寸
	char *sql_find = "SELECT id FROM lockers WHERE status = '空闲' AND size = ? LIMIT 1";
	rc = sqlite3_prepare_v2(db, sql_find, -1, &stmt, 0);
	if(rc != SQLITE_OK){
	    perror("do_delivery:sqlite3_prepare_v2");
	    sqlite3_close(db);
	    strcpy(buf+1, "快递柜查询失败");
	    return -1;
	}
	sqlite3_bind_text(stmt, 1, sizeText, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if(rc == SQLITE_ROW){
	    //获取空闲的柜子编号
	    uint8_t locker_id = sqlite3_column_int(stmt, 0);

	    //更新柜子状态为'占用'
	    char *sql_update = "UPDATE lockers SET status = '使用中',"
		    " package_no = ?, courier_phone = ?, delivery_company = ?, "
		    " delivery_time = datetime('now', 'localtime'), recipient_phone = ?, "
		    " pickup_code = printf('%08d', ABS(random() % 100000000) ) "
		    " WHERE id = ? ";
	    sqlite3_finalize(stmt);
	    rc = sqlite3_prepare_v2(db, sql_update, -1, &stmt, 0);
	    if(rc != SQLITE_OK){
	        perror("无法准备声明");
		sqlite3_close(db);
		strcpy(buf+1, "更新柜子状态失败");
		return -1;
	    }
	    //绑定参数
	    sqlite3_bind_text(stmt, 1, courier_number, -1, SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 2, courier.number, -1, SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 3, courier.company, -1, SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 4, recipient_phone, -1, SQLITE_STATIC);
	    sqlite3_bind_int(stmt, 5, locker_id);

	    //执行更新语句
	    rc = sqlite3_step(stmt);
	    if(rc != SQLITE_DONE){
	        perror("更新柜子状态失败");
		strcpy(buf+1, "更新柜子状态失败");
		return -1;
	    }
	    printf("%d快递已存入\n", locker_id);
	    buf[0] = locker_id;
	    sprintf(&buf[1], "快递已存入%d号柜子。", locker_id);
	    sqlite3_finalize(stmt);
	    sprintf(buf, "%d", locker_id);
	}else{
	    printf("没有找到合适的空闲快递柜。\n");
	    strcpy(buf+1, "没有找到合适的空闲快递柜。");
	    return -1;
	}
	//strcpy(buf, "ok");
	//关闭数据库连接
	sqlite3_close(db);
	return 0;
}
