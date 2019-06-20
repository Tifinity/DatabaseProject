#pragma once
//销售记录
class Sell {
public:
	int get_total_sales(int month);//获取某月的销售总额
	int get_total_number(int month);//获取某月的销售总量
	void get_top_ten_books(int month);//输出某月销量前10的书
};