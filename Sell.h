#pragma once
#include "mysql.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Sell {
private:
    MYSQL m;
    string bid;
    string cid;
    string date;
public:
    Sell(MYSQL m_);
    bool find_book();
    int get_inventory();
    void update_book_table();
    void update_sell_table();
    void print_sell_list();
    void set_values(string bid_, string cid_, string date_){
        bid = bid_;
        cid = cid_; 
        date = date_;
    };
    bool sell();
};