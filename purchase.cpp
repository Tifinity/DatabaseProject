#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "mysql.h"
#include "purchase.h"
using namespace std;

PurchaseBook::PurchaseBook(MYSQL m_)
{
    if (mysql_query(&m_, "create table purchase_book(sname char(20) not null, bname char(20) not null, sdate char(20) not null, primary key(sname,bname,sdate))") != 0)
    {
        cout << "create table return fail!" << endl << endl;
        cout << mysql_error(&m_) << endl;
    }
    m = m_;
}

int PurchaseBook::get_inventory()
{
    string sql = "select * from book where bid='";
    sql += bid;
    sql += "'";

    if (mysql_query(&m, sql.c_str()) == 0)
    {
        MYSQL_RES *res = mysql_store_result(&m);
        if (res)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            stringstream ss;
            int num = 0;
            ss << row[2];
            ss >> num;
            return num;
        }
    }
    return 0;
}

int PurchaseBook::determine_quantity(int year, int month, MYSQL m)
{
    int number = 0;
    if (get_inventory() > 5)
        return number;
    else if (get_inventory() <= 5 && get_inventory() >= 0)
    {
        char strquery[1000] = "select b.bid as book_id, b.bname as book_name, sum(s.num) as sales_number "
            "from book as b, sell as s where b.bid = s.bid and s.sdate like '";
        char _year[5], _month[3];
        for (int i = 3; i >= 0; --i)
        {
            if (year == 0)
                _year[i] = '0';
            _year[i] = year % 10 + '0';
            year /= 10;
        }
        for (int i = 1; i >= 0; --i)
        {
            if (month == 0)
                _month[i] = '0';
            _month[i] = month % 10 + '0';
            month /= 10;
        }
        _year[4] = '\0';
        _month[2] = '\0';
        strcat_s(strquery, _year);
        strcat_s(strquery, "-");
        strcat_s(strquery, _month);
        strcat_s(strquery, "-%'group by s.bid order by sales_number desc;");
        if (mysql_query(&m, strquery) == 0)
        {
            MYSQL_RES *result = mysql_store_result(&m);
            MYSQL_ROW row;
            int j = 1;
            while ((row = mysql_fetch_row(result)) != NULL)
            {
                if (row[0] == bid)
                {
                    if (j <= 10)
                        number = int(row[2]) * (1 + (10 - j)*0.1);
                    else
                        number = max(int(row[2]) * (1 - (j - 10)*0.01), int(row[2]) * 0.5);
                }
                j++;
            }
        }
        else
            cout << "Error in query!" << endl;
        return number;
    }
}


string PurchaseBook::choose_supplier(MYSQL &m)
{
    char strquery[1000] = "select b.bid as book_id, b.bname as book_name, s.sid as supply_id, ser.sname as supplier_name, s.sprice as supply_price "
        "from book as b, supplier as ser, supply as s where b.bid = s.bid and ser.sid = s.sid;";
    string str = "No supplier";
    if (mysql_query(&m, strquery) == 0)
    {
        MYSQL_RES *result = mysql_store_result(&m);
        MYSQL_ROW row;
        row = mysql_fetch_row(result);
        int j = int(row[4]);
        str = row[1];
        while ((row = mysql_fetch_row(result)) != NULL)
        {
            if (int(row[4]) < j)
            {
                j = int(row[4]);
                str = row[1];
            }
        }
        return str;
    }
    else
        return str;
}

void PurchaseBook::setValue(string sname_, string bname_, string sdate_)
{
    sname = sname_;
    bname = bname_;
    sdate = sdate_;
}

void PurchaseBook::print_purchase_list()
{
    cout << "     Return List" << endl;
    cout << choose_supplier(m);
    cout << " " << bname << " " << sdate << " ";
}

void PurchaseBook::update_book_table()
{
    stringstream ss;
    string str;
    string strquery1 = "update book b set b.bnum=b.bnum+ ";
    ss << determine_quantity(year, month, m);
    ss >> str;
    strquery1 + str;
    strquery1 + " where b.bid='";
    strquery1 + bid;
    strquery1 + "';";
}

void PurchaseBook::add_purchase_info()
{
    stringstream ss;
    string str;
    ss << sprice;
    ss >> str;
    string strquery = "insert into purchase_book(sname,bname,sdate,sprice) values('";
    strquery + choose_supplier(m);
    strquery + "','";
    strquery + bname;
    strquery + "','";
    strquery + sdate;
    strquery + "','";
    strquery + str;
    strquery + "');";
}

void PurchaseBook::Purchase()
{
    if (get_inventory() <= 5 && get_inventory() >= 0)
    {
        print_purchase_list();
        update_book_table();
        add_purchase_info();
    }
    else
    {
        cout << "purchase fail!" << endl;
    }
}