#include<iostream>
#include<cstdlib>
#include<string.h>
#include<winsock.h>
#include "mysql.h"
MYSQL mysql;

using namespace std;
void init() {
    if (mysql_query(&mysql, "create table book (bid char(20) not null primary key, bname char(20), bnum int, bprice int)") == 0) {
        cout << "create table book successfully" << endl;
    }
    else {
        cout << "create table book failed" << endl;
    }

    if (mysql_query(&mysql, "create table customer (cid char(20) not null primary key, cname char(20))") == 0) {
        cout << "create table customer successfully" << endl;
    }
    else {
        cout << "create table cuetomer failed" << endl;
    }

    if (mysql_query(&mysql, "create table supplier (sid char(20) not null primary key, sname char(20))") == 0) {
        cout << "create table supplier successfully" << endl;
    }
    else {
        cout << "create table supplier failed" << endl;
    }

    if (mysql_query(&mysql, "create table sell (cid char(20), bid char(20), date char(20), primary key(cid, bid), foreign key(cid) references customer(cid), foreign key(bid) references book(bid) )") == 0) {
        cout << "create table sell successfully" << endl;
    }
    else {
        cout << "create table sell failed" << endl;
    }

    if (mysql_query(&mysql, "create table supply (sid char(20), bid char(20), sprice int, primary key(sid, bid), foreign key(sid) references supplier(sid), foreign key(bid) references book(bid) )") == 0) {
        cout << "create table supply successfully" << endl;
    }
    else {
        cout << "create table supply failed" << endl;
    }
}

int main() {
    char op;
    mysql_init(&mysql);		

    if (mysql_real_connect(&mysql, "localhost", "root", "tianHAOyuQI361", "bookshop", 3306, 0, 0)) {
        init();
        while (true) {
            cout << "请键入相应键位以执行功能: " << endl << endl;
            cout << "0--exit" << endl;
            cout << "1--创建学生表   6--添加成绩记录   b--删除课程记录   h--学生课程成绩表" << endl;
            cout << "2--创建课程表   7--修改学生记录   c--删除成绩记录   j--学生成绩统计表" << endl;
            cout << "3--创建成绩表   8--修改课程记录   e--显示学生记录   k--课程成绩统计表" << endl;
            cout << "4--添加学生记录 9--修改成绩记录   f--显示课程记录   m--数据库表名" << endl;
            cout << "请输入: ";
            cin >> op;
            switch (op) {
            case '0':
                exit(0);
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            default:
                cout << "功能尚未实现" << endl;
            }
        }
    }
    else
        cout << "数据库连接失败" << endl;
    mysql_close(&mysql);
    return 0;
}