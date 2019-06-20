#include"sell.h"
#include<string>
#include<iostream>
using namespace std;


int Sell::get_total_sales(int year, int month,MYSQL &mysql) {
	int total = 0;
	char strquery[1000] = "select sum(b.bprice*s.num ) as total_sales "
		"from book as b, sell as s where b.bid = s.bid "
		"and s.sdate like '";
	char _year[5], _month[3];
	for (int i = 3; i >= 0; --i) {
		if (year == 0) _year[i] = '0';
		_year[i] = year % 10 + '0';
		year /= 10;
	}
	for (int i = 1; i >= 0; --i) {
		if (month == 0) _month[i] = '0';
		_month[i] = month % 10 + '0';
		month /= 10;
	}
	_year[4] = '\0';
	_month[2] = '\0';
	strcat(strquery, _year);
	strcat(strquery, "-");
	strcat(strquery, _month);
	strcat(strquery, "-%';");
	if (mysql_query(&mysql, strquery)==0) {

		MYSQL_RES *result = mysql_store_result(&mysql);
		MYSQL_ROW row;
		int num_fields = mysql_field_count(&mysql);
		while ((row = mysql_fetch_row(result)) != NULL) {
			for (int i = 0; i < num_fields; ++i)
				total = atoi(row[i]);
		}
		mysql_free_result(result);
	}
	else cout << "Error in query!" << endl;
	return total;
}

int Sell::get_total_number(int year, int month, MYSQL &mysql) {
	int total;
	char strquery[1000] = "select sum(s.num) as total_number from book as b, sell as s "
		"where b.bid=s.bid and s.sdate like '";
	char _year[5], _month[3];
	for (int i = 3; i >= 0; --i) {
		if (year == 0) _year[i] = '0';
		_year[i] = year % 10 + '0';
		year /= 10;
	}
	for (int i = 1; i >= 0; --i) {
		if (month == 0) _month[i] = '0';
		_month[i] = month % 10 + '0';
		month /= 10;
	}
	_year[4] = '\0';
	_month[2] = '\0';
	strcat(strquery, _year);
	strcat(strquery, "-");
	strcat(strquery, _month);
	strcat(strquery, "-%';");
	if (mysql_query(&mysql, strquery)==0) {
		MYSQL_RES *result = mysql_store_result(&mysql);
		MYSQL_ROW row;
		int num_fields = mysql_field_count(&mysql);
		while ((row = mysql_fetch_row(result)) != NULL) {
			for (int i = 0; i < num_fields; ++i)
				total = atoi(row[i]);
		}
	}
	else cout << "Error in query!" << endl;
	return total;
}

void Sell::get_top_ten_books(int year, int month, MYSQL &mysql) {
	char strquery[1000] = "select b.bid as book_id, b.bname as book_name, sum(s.num) as sales_number "
		"from book as b, sell as s where b.bid = s.bid and s.sdate like '";
	char _year[5], _month[3];
	for (int i = 3; i >= 0; --i) {
		if (year == 0) _year[i] = '0';
		_year[i] = year % 10 + '0';
		year /= 10;
	}
	for (int i = 1; i >= 0; --i) {
		if (month == 0) _month[i] = '0';
		_month[i] = month % 10 + '0';
		month /= 10;
	}
	_year[4] = '\0';
	_month[2] = '\0';
	strcat(strquery, _year);
	strcat(strquery, "-");
	strcat(strquery, _month);
	strcat(strquery, "-%'group by s.bid order by sales_number desc;");
	if (mysql_query(&mysql, strquery)==0) {
		MYSQL_RES *result = mysql_store_result(&mysql);
		MYSQL_ROW row;
		int j = 1;
		while ((row = mysql_fetch_row(result)) != NULL) {
			cout << j++ << ". ";
			for (int i = 0; i < 3; ++i)
				cout << row[i] << " ";
			cout << endl;
		}
	}
	else cout << "Error in query!" << endl;
}