#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <graphics.h>
#include <windows.h>
#include "basic_math.h"
using namespace std;
using namespace ege;

struct LUJNG {
	short x;
	short y;
	bool m;
	void cmd_show() {
		cout<<"x="<<x<<",y="<<y<<",是否为调制点="<<m<<endl; 
	}
	void set(int nx,int ny) {
		x=nx;
		y=ny;
	}
};
struct PT {
	short x;
	short y;
	void pset(int nx,int ny) {
		x=nx;
		y=ny;
	}
	void set(LUJNG luj) {
		x=luj.x;
		y=luj.y;
	}
	void out() {
		cout<<"("<<x<<","<<y<<")";
	}
};
void line_(int x1,int y1,int x2,int y2) {
	//cout<<"      LINE "<<x1<<","<<y1<<" "<<x2<<","<<y2<<endl;
	line(x1,y1,x2,y2);
}
void draw_bseqx(PT pos, double scale, PT tst, PT tsp, PT p_pt[16], int lgth,int color) {
	//cout<<"-------###----LENGTH="<<lgth<<endl;
	double p_x_array[16];
	double p_y_array[16];
	memset(p_x_array,0,128);
	memset(p_y_array,0,128);
	double ip_x_array[16];
	double ip_y_array[16];
	memset(ip_x_array,0,128);
	memset(ip_y_array,0,128);
	
	if (lgth==2) {
		setcolor(color);
		line_(tst.x+pos.x,pos.y-tst.y,tsp.x+pos.x,pos.y-tsp.y);
		return;
	}
	
	p_x_array[0]=tst.x;
	p_y_array[0]=tst.y;
	p_x_array[lgth-1]=tsp.x;
	p_y_array[lgth-1]=tsp.y;
	for (int i=1;i<lgth-1;i++) {
		p_x_array[i]=p_pt[i-1].x;
		p_y_array[i]=p_pt[i-1].y;
	}
	
		//cout<<" **********LIST"<<endl; 
	for (int i=0;i<lgth;i++) {
		ip_x_array[i]=pos.x+(scale*p_x_array[i]);
		ip_y_array[i]=pos.y-(scale*p_y_array[i]);
		setcolor(0xffff00);
		circle(ip_x_array[i],ip_y_array[i],2);
		//cout<<i<<" - "<<ip_x_array[i]<<","<<ip_y_array[i]<<endl;
	}
		//cout<<" **********LIST END"<<endl; 
	
	cout<<endl;
	
	double tempx=0,tempy=0;
	double pvx=0,pvy=0;

	double rt=abslength(ip_x_array[0],ip_y_array[0],ip_x_array[lgth-1],ip_y_array[lgth-1]); //假装估算曲线长度 
	double pc;
	for (int step=0;step<=(int)rt;step++) {
		setcolor(color);
		pc=step/rt;
		tempx=0,tempy=0;
		for (int i=0;i<=lgth;i++) {
			tempx+=binparam(i,lgth-1,pc)*ip_x_array[i];
			tempy+=binparam(i,lgth-1,pc)*ip_y_array[i];
		}
		if (step==0) {
			line(ip_x_array[0],ip_y_array[0],tempx,tempy);
			pvx=tempx,pvy=tempy;
		}
		line(pvx,pvy,tempx,tempy);
		pvx=tempx,pvy=tempy;
	}
}
struct BIHUA {
	char name[16];
	int lgth;
	LUJNG luj[16];
	void cmd_list() {
		cout<<"=============="<<endl;
		cout<<"名:"<<name<<endl;
		cout<<"长度:"<<lgth<<endl; 
		for (int i=0;i<lgth;i++)luj[i].cmd_show();
		cout<<endl;
	}
	void add_luj(int p) {
		cout<<"Insert a new point at "<<p<<endl;
		if (lgth>=15) {
			cout<<"ERR: BIHUA has been totally filled already!"<<endl;
			return;
		}
		for (int i=lgth;i>=p;i--) {
			luj[i+1]=luj[i];
		}
		luj[p].set((luj[p-1].x+luj[p+1].x)/2,(luj[p-1].y+luj[p+1].y)/2);
		lgth++;
	}
	void del_luj(int p) {
		cout<<"Delete a point at "<<p<<endl;
		if (lgth==1) {
			return;
		}
		if (p>lgth-1) {
			cout<<"ERR: Did nothing."<<endl;
			return;
		}
		for (int i=p;i<=lgth;i++) {
			luj[i]=luj[i+1];
		}
		lgth--;
	}
	void draw_bih(PT pos,double scale,int color) {
		PT t1,t2;
		PT p[16];
		//cout<<"========*===Draw bihua"<<endl;
		int t=2,l=0;
		for (int i=0;i<lgth;i++) {
			if (i==0) {
				t1.set(luj[0]);
			}
			if (luj[i].m==0) {
				//cout<<"i="<<i<<" ";
				t2.set(luj[i]);
				//draw
				//pos.out();
				//t1.out();
				//t2.out();
				//cout<<" "<<tendl;
				draw_bseqx(pos,scale,t1,t2,p,t,color);
				//other
				memset(p,0,16*sizeof(PT));
				t1=t2;
				t=2;
				l=0;
			} else {
				//cout<<"#############DETECT MPOINT"<<endl;
				p[l].set(luj[i]);
				l++;
				t++;
			}
		}
	}
};
struct BUJAN {
	char name[16];
	int lgth;
	BIHUA bih[16];
	void add_bih() {
		if (lgth>=15) {
			cout<<"ERR: BUJAN has been totally filled already!"<<endl;
			return;
		}
		lgth++;
	}
	void del_bih(int p) {
		cout<<"Delete a bihua at "<<p<<endl;
		if (lgth==1) {
			return;
		}
		if (p>lgth) {
			cout<<"ERR: Did nothing."<<endl;
			return;
		}
		for (int i=p;i<=lgth;i++) {
			bih[i]=bih[i+1];
		}
		lgth--;
	}
	void draw_buj(PT pos,double scale,int color){
		//cout<<"====*===Draw bujian"<<endl;
		for (int i=0;i<lgth;i++) {
			bih[i].draw_bih(pos,scale,color);
		}
	}
};
struct HANZI {
	char name[16];
	int lgth;
	BUJAN buj[8];
	void add_buj() {
		if (lgth>=7) {
			cout<<"ERR: HANZI has been totally filled already!"<<endl;
			return;
		}
		lgth++;
	}
	void del_buj(int p) {
		cout<<"Delete a bujan at "<<p<<endl;
		if (lgth==1) {
			return;
		}
		if (p>lgth) {
			cout<<"ERR: Did nothing."<<endl;
			return;
		}
		for (int i=p;i<=lgth;i++) {
			buj[i]=buj[i+1];
		}
		lgth--;
	}
	void draw_han(PT pos,double scale,int color) {
		//cout<<"*===Draw hanzi"<<endl;
		for (int i=0;i<lgth;i++) {
			buj[i].draw_buj(pos,scale,color);
		}
	}
	void init() {
		memset(this,0,sizeof(HANZI));
		lgth=1;
		buj[0].lgth=1;
		buj[0].bih[0].lgth=1;
	}
};

#endif
