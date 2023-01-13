#ifndef _BASIC_MATH_H_
#define _BASIC_MATH_H_

#include <iostream>
#include <math.h>
using namespace std;
double jc(int i) {
	int temp=1;
	for (int j=i;j>0;) {
		temp*=j--;
	}
	return temp;
}
int comb(int m, int n) {
	//cout<<"C("<<m<<","<<n<<")"<<endl;
	
	if (n==0)return 1;
	return jc(m)/jc(n)/jc(m-n);
}
double binparam(int i, int n, double t) {
	return comb(n,i)*pow(t,n-i)*pow(1-t,i);
}
double abslength(double x1,double x2,double y1,double y2) {
	return pow(pow(x1-x2,2)+pow(y1-y2,2),0.5);
}

#endif
