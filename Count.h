#pragma once
#include "mysql.h"

class Count{
public:
    int get_total_sales(int year, int month, MYSQL &mysql);//��ȡĳ�µ������ܶ�
    int get_total_number(int year, int month, MYSQL &mysql);//��ȡĳ�µ���������
    void get_top_ten_books(int year, int month, MYSQL &mysql);//���ĳ������ǰ10����
};