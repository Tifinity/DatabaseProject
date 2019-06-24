#include"ReturnBook.h"
void ReturnBook::updateSellRecord(char* cid,char* bid,char* sdate) {
	char strquery[100] = "select num from sell where cid='";
	strcat(strquery, cid);
	strcat(strquery, "'");
	strcat(strquery, " and bid='");
	strcat(strquery, bid);
	strcat(strquery, "'");
	strcat(strquery, " and sdate='");
	strcat(strquery, sdate);
	strcat(strquery, "';");
	if (mysql_query(&m, strquery) != 0) {
		printf("query fail!\n");
	}
	char num[10];
	MYSQL_RES *res = mysql_store_result(&m);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		strcpy(num, row[0]);
	}
	string snum = num;
	if (snum == "1") {
		char strquery1[100] = "delete from sell where cid='";
		strcat(strquery1, cid);
		strcat(strquery1, "'");
		strcat(strquery1, " and bid='");
		strcat(strquery1, bid);
		strcat(strquery1, "'");
		strcat(strquery1, " and sdate='");
		strcat(strquery1, sdate);
		strcat(strquery1, "';");
		if (mysql_query(&m, strquery1) != 0) {
			printf("query fail!\n");
		}
	}
	else {
		char strquery1[100] = "update sell set num=num-1 where cid='";
		strcat(strquery1, cid);
		strcat(strquery1, "'");
		strcat(strquery1, " and bid='");
		strcat(strquery1, bid);
		strcat(strquery1, "'");
		strcat(strquery1, " and sdate='");
		strcat(strquery1, sdate);
		strcat(strquery1, "';");
		if (mysql_query(&m, strquery1) != 0) {
			printf("query fail!\n");
		}
	}
}
ReturnBook::ReturnBook(MYSQL m_) {
	if (mysql_query(&m_, "create table return_book(cname char(20) not null, bname char(20) not null, rdate char(20) not null, primary key(cname,bname,rdate))") != 0) {
		printf("create table return fail!\n\n");
        cout << mysql_error(&m_) << endl;
	}
	m = m_;
}
void ReturnBook::setValue(string cusName_, string bookName_, string sdate_, string rdate_) {
	cusName = cusName_;
	bookName = bookName_;
	sdate = sdate_;
	rdate = rdate_;
}
bool ReturnBook::check() {
	char strquery1[100] = "select bid from book b where b.bname='";
	MYSQL_ROW row;
	strcat(strquery1, bookName.c_str());
	strcat(strquery1, "';");
	if (mysql_query(&m, strquery1) == 0) {
		MYSQL_RES *res = mysql_store_result(&m);
		if (res != NULL) {
			row = mysql_fetch_row(res);
			strcpy(bid, row[0]);
		}
		else {
			printf("invalid book name!\n");
			return false;
		}
	}
	else {
		printf("query fail!\n");
		return false;
	}
	char strquery2[100] = "select cid from customer c where c.cname='";
	char cid[20];
	strcat(strquery2, cusName.c_str());
	strcat(strquery2, "';");
	if (mysql_query(&m, strquery2) == 0) {
		MYSQL_RES *res = mysql_store_result(&m);
		if (res != NULL) {
			row = mysql_fetch_row(res);
			strcpy(cid, row[0]);
		}
		else {
			printf("invalid customer name!\n");
			return false;
		}
	}
	else {
		printf("query fail!\n");
		return false;
	}
	char strquery3[100] = "select * from sell where cid='";
	char sell_id[20];
	strcat(strquery3, cid);
	strcat(strquery3, "'");
	strcat(strquery3, " and bid='");
	strcat(strquery3, bid);
	strcat(strquery3, "'");
	strcat(strquery3, " and sdate='");
	strcat(strquery3, sdate.c_str());
	strcat(strquery3, "';");
	if (mysql_query(&m, strquery3) == 0) {
		MYSQL_RES *res = mysql_store_result(&m);
		if (res != NULL) {
			updateSellRecord(cid,bid,(char*)sdate.c_str());
			return true;
		}
		else {
			printf("invalid return info!\n");
			return false;
		}
	}
	else {
		printf("query fail!\n");
		return false;
	}
}
void ReturnBook::updateStock() {
	char strquery1[100] = "update book b set b.bnum=b.bnum+1 where b.bid='";
	strcat(strquery1, bid);
	strcat(strquery1, "';");
	if (mysql_query(&m, strquery1) != 0) {
		printf("query fail!\n");
	}
}
void ReturnBook::printReturnList() {
	printf("     Return List\n");
	cout << cusName << " " << bookName << " " << sdate << endl;
}
void ReturnBook::addReturnInfo() {
	char strquery[100] = "insert into return_book(cname,bname,rdate) values('";
	strcat(strquery, cusName.c_str());
	strcat(strquery, "','"); 
	strcat(strquery, bookName.c_str());
	strcat(strquery, "','");
	strcat(strquery, rdate.c_str());
	strcat(strquery, "');");
	if (mysql_query(&m, strquery) != 0) {
		printf("query fail!\n");
	}
}
void ReturnBook::Return() {
	if (check()) {
		printReturnList();
		updateStock();
		addReturnInfo();
	}
	else {
		printf("check fail!\n");
	}
}