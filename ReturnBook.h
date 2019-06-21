#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include "mysql.h"
using namespace std;

class ReturnBook {
public:
	ReturnBook(MYSQL m_);
	void setValue(string cusName_, string bookName_, string sdate_, string rdate_);
	bool check();
	void deleteSellTuple(char* src);
	void updateStock();
	void printReturnList();
	void addReturnInfo();
	void Return();
private:
	MYSQL m;
	string cusName;
	string bookName;
	string sdate;
	string rdate;
	char bid[20];
};