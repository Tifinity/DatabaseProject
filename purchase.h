#pragma once
#include "mysql.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

class PurchaseBook
{
public:
    PurchaseBook(MYSQL m_);
    int get_inventory();
    int determine_quantity(int year, int month, MYSQL m);
    string choose_supplier(MYSQL &m);
    void setValue(string sname_, string bname_, string sdate_);
    void print_purchase_list();
    void update_book_table();
    void Purchase();
    void add_purchase_info();

private:
    MYSQL m;
    string bid;
    string sid;
    string sdate;
    string bname;
    string sname;
    int sprice;
    int year;
    int month;
};