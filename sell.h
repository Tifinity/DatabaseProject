#pragma once
#include "mysql.h"

//���ۼ�¼
class Sell {
public:
	int get_total_sales(int year,int month,MYSQL &mysql);//��ȡĳ�µ������ܶ�
	int get_total_number(int year,int month, MYSQL &mysql);//��ȡĳ�µ���������
	void get_top_ten_books(int year,int month, MYSQL &mysql);//���ĳ������ǰ10����
};