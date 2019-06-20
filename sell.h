#pragma once
#include "mysql.h"

//销售记录
class Sell {
public:
	int get_total_sales(int year,int month,MYSQL &mysql);//获取某月的销售总额
	int get_total_number(int year,int month, MYSQL &mysql);//获取某月的销售总量
	void get_top_ten_books(int year,int month, MYSQL &mysql);//输出某月销量前10的书
};