#include<iostream>
#include<cstdlib>
#include<string.h>
#include<winsock.h>
#include "Sell.h"
#include "Count.h"
#include "ReturnBook.h"

using namespace std;

void init(MYSQL &mysql) {
    mysql_query(&mysql, "drop table if exists sell");
    mysql_query(&mysql, "drop table if exists supply");
    mysql_query(&mysql, "drop table if exists book");
    mysql_query(&mysql, "drop table if exists customer");
    mysql_query(&mysql, "drop table if exists supplier");//?????? 不能删啊
    
    if (mysql_query(&mysql, "create table book (bid char(20) not null, bname char(20), bnum int, bprice int, primary key(bid))") == 0) {
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

    if (mysql_query(&mysql, "create table sell (cid char(20), bid char(20), sdate char(20), primary key(cid, bid, sdate), foreign key(cid) references customer(cid), foreign key(bid) references book(bid) )") == 0) {
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
    MYSQL mysql;
    mysql_init(&mysql);		
    if (mysql_real_connect(&mysql, "localhost", "root", "123456", "bookshop", 3306, 0, 0)) {
        init(mysql);
        ReturnBook RB(mysql);
        Sell SL(mysql);
        while (true) {
            cout << "请键入相应键位以执行功能: " << endl << endl;
            cout << "0--exit" << endl;
            cout << "1--进货" << endl;
            cout << "2--退货" << endl;
            cout << "3--销售" << endl;
            cout << "4--统计" << endl;
            cout << "请输入: ";
            cin >> op;
            switch (op) {
            case '0':
                exit(0);
                break;
            case '1':
                break;
            case '2': {
                string cusName, bookName, sdate, rdate;
                cout << "请输入顾客姓名" << endl;
                cin >> cusName;
                cout << "请输入退还书名" << endl;
                cin >> bookName;
                cout << "请输入购买时间" << endl;
                cin >> sdate;
                cout << "请输入退还时间" << endl;
                cin >> rdate;
                RB.setValue(cusName, bookName, sdate, rdate);
                RB.Return();
            }

                break;
            case '3': {
                string bid;
                string cid;
                string date;
                cout << "请输入bid" << endl;
                cin >> bid;
                cout << "请输入顾客id" << endl;
                cin >> cid;
                cout << "请输入购买日期" << endl;
                cin >> date;
                SL.set_values(bid, cid, date);
                int num = SL.get_inventory();
                if (num) {
                    cout << "库存量：" << num << endl;
                    SL.update_book_table();
                    SL.update_sell_table();
                    SL.print_sell_list();
                }
                else {
                    cout << "该书已卖完" << endl;
                }

                break;
            }
            case '4':
                Count c;
                cout << "请输入要查询的年、月：" << endl;
                int year, month;
                cin >> year >> month;
                cout << "当月销售总额：" << c.get_total_sales(year, month, mysql) << " 元" << endl << endl;
                cout << "当月销售总量：" << c.get_total_number(year, month, mysql) << " 本" << endl << endl;
                cout << "当月销量排行榜：排名/书号/书名/销量(本)" << endl;
                c.get_top_ten_books(year, month, mysql);
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