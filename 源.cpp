#include<iostream>
#include<cstdlib>
#include<string.h>
#include<winsock.h>
#include "purchase.h"
#include "Sell.h"
#include "Count.h"
#include "ReturnBook.h"

using namespace std;

void init(MYSQL &mysql) {
    if (mysql_query(&mysql, "create table if not exists book (bid char(20) not null, bname char(20), bnum int, bprice int, primary key(bid))") == 0) {
        cout << "create table book successfully" << endl;
    }
    else {
        cout << "create table book failed" << endl;
    }

    if (mysql_query(&mysql, "create table if not exists customer (cid char(20) not null primary key, cname char(20))") == 0) {
        cout << "create table customer successfully" << endl;
    }
    else {
        cout << "create table cuetomer failed" << endl;
    }

    if (mysql_query(&mysql, "create table if not exists supplier (sid char(20) not null primary key, sname char(20))") == 0) {
        cout << "create table supplier successfully" << endl;
    }
    else {
        cout << "create table supplier failed" << endl;
    }

    if (mysql_query(&mysql, "create table if not exists sell (cid char(20), bid char(20), sdate char(20), primary key(cid, bid, sdate), foreign key(cid) references customer(cid), foreign key(bid) references book(bid) )") == 0) {
        cout << "create table sell successfully" << endl;
    }
    else {
        cout << "create table sell failed" << endl;
    }
}

int main() {
    char op;
    MYSQL mysql;
    mysql_init(&mysql);		
    
    if (mysql_real_connect(&mysql, "localhost", "root", "tianHAOyuQI361", "bookshop", 3306, 0, 0)) {
        init(mysql);
        PurchaseBook PC(mysql);
        ReturnBook RB(mysql);
        Sell SL(mysql);
        Count C;
        while (true) {
            cout << "�������Ӧ��λ��ִ�й���: " << endl << endl;
            cout << "0--exit" << endl;
            cout << "1--����" << endl;
            cout << "2--�˻�" << endl;
            cout << "3--����" << endl;
            cout << "4--ͳ��" << endl;
            cout << "������: ";
            cin >> op;
            switch (op) {
            case '0':
                exit(0);
                break;
            case '1': {
                cout << "�����뵱ǰ���ꡢ�£�" << endl;
                int year, month;
                string bid;

                cin >> year >> month;
                cout << "�������鼮id" << endl;
                cin >> bid;
                PC.Purchase();
                break;
            } 
            case '2': {
                string cusName, bookName, sdate, rdate;
                cout << "������˿�����" << endl;
                cin >> cusName;
                cout << "�������˻�����" << endl;
                cin >> bookName;
                cout << "�����빺��ʱ��" << endl;
                cin >> sdate;
                cout << "�������˻�ʱ��" << endl;
                cin >> rdate;
                RB.setValue(cusName, bookName, sdate, rdate);
                RB.Return();
                break;
            }
            case '3': {
                string bid;
                string cid;
                string date;
                cout << "������bid" << endl;
                cin >> bid;
                cout << "������˿�id" << endl;
                cin >> cid;
                cout << "�����빺������" << endl;
                cin >> date;
                SL.sell(bid, cid, date);
                break;
            }
            case '4':
                cout << "������Ҫ��ѯ���ꡢ�£�" << endl;
                int year, month;
                cin >> year >> month;
                cout << "���������ܶ" << C.get_total_sales(year, month, mysql) << " Ԫ" << endl << endl;
                cout << "��������������" << C.get_total_number(year, month, mysql) << " ��" << endl << endl;
                cout << "�����������а�����/���/����/����(��)" << endl;
                C.get_top_ten_books(year, month, mysql);
                break;
            default:
                cout << "������δʵ��" << endl;
            }
        }
    }
    else
        cout << "���ݿ�����ʧ��" << endl;
    mysql_close(&mysql);
    return 0;
}