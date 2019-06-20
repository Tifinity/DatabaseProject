#include"ReturnBook.h"
void ReturnBook::deleteSellTuple(char* src) {
	char strquery1[100] = "delete from sell s where s.sell_id='";
	strcat(strquery1, src);
	strcat(strquery1, "';");
	if (mysql_query(&m, strquery1) != 0) {
		printf("query fail!\n");
	}
}
ReturnBook::ReturnBook(MYSQL m_) {
	if (mysql_query(&m, "create table return ( cname char(20) not null, bname char(20) not null,rdate char(20) not null, primary key(cname,bname,rdate));") != 0) {
		printf("create table return fail!\n\n");
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
	char strquery3[100] = "select sell_id from sell s where s.cid='";
	char sell_id[20];
	strcat(strquery3, cid);
	strcat(strquery3, "'");
	strcat(strquery3, " and s.bid='");
	strcat(strquery3, bid);
	strcat(strquery3, "'");
	strcat(strquery3, " and s.sdate='");
	strcat(strquery3, sdate.c_str());
	strcat(strquery3, "';");
	if (mysql_query(&m, strquery3) == 0) {
		MYSQL_RES *res = mysql_store_result(&m);
		if (res != NULL) {
			deleteSellTuple(sell_id);
			return true;
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
}
void ReturnBook::updateStock() {
	char strquery1[100] = "update book b set b.bnum=b.bnum-1 where b.bid='";
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
	char strquery[100] = "insert into return(cname,bname,rdate) values('";
	strcat(strquery, cusName.c_str());
	strcat(strquery, "','"); 
	strcat(strquery, bookName.c_str());
	strcat(strquery, "','");
	strcat(strquery, rdate.c_str());
	strcat(strquery, "');");
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