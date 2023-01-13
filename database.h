#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <iostream>
#include <fstream>
#include <windows.h> 
#include "data.h"

using namespace std;

ifstream fi_table;
ofstream fo_table;
const char _hex[]="0123456789ABCDEF";
const char fn_table[]="TABLE.BIN";
BUJAN lbuj;
struct 
unsigned int address_data;
void out_char(unsigned char c) {
	cout<<_hex[c/0x10]<<_hex[c%0x10];
}
void out_short(unsigned short c) {
	out_char(c/0x100);
	out_char(c%0x100);
}
void out_int(unsigned int c) {
	out_short(c/0x10000);
	out_short(c%0x10000);
}
void input_table() {
	fi_table.open(fn_table);
	fi_table.read((char*)&address_data,4);
	cout<<"DATA ADDRESS = 0x";
	out_int(address_data);
	cout<<endl;
	fi_table.close();
}
void read_flag_on() {
	fi_table.open(fn_table);
	//fi_table.read((char*)&address_data,4);
}
void 
void search() {
	
}

#endif
