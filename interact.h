/*
交互 
------------------- 
循环中加入代码:
click_update();
xxx.update();
xxx.draw();
不要忘了在之前
xxx.init(); 
*/

#ifndef _INTERACT_H_
#define _INTERACT_H_

#include <windows.h>
#include <iostream>
#include <graphics.h>

#define KEY_DOWN(VK_NONAME) ((GetKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define mx msmsg.x
#define my msmsg.y
#define tx mx-256
#define ty 272-my

using namespace std;
using namespace ege;

bool is_inside(int x,int y,int x1,int y1,int x2,int y2) {
	int _x1=(x1>x2)?x2:x1;
	int _x2=(x1>x2)?x1:x2;
	int _y1=(y1>y2)?y2:y1;
	int _y2=(y1>y2)?y1:y2;
	return (x >= _x1 && x <= _x2 && y >= _y1 && y <= _y2);
}
mouse_msg msmsg;
bool click_temp_prev;
bool click_temp_next;
bool is_release,is_pressed;
void click_update() {
	click_temp_prev=click_temp_next;
	click_temp_next=KEY_DOWN(VK_LBUTTON);
	is_release=(click_temp_prev==1 && click_temp_next==0);
	is_pressed=(click_temp_prev==0 && click_temp_next==1);
}
class BUTTON {
	private:
		unsigned char state;
		bool clicked_flag;
		//l->h 悬停 单击 
		int x;
		int y;
		int w;
		int h;
		int color1; //边框 
		int color2; //默认填充 
		int color3; //悬停填充
		int color4; //按下填充 
		int color5; //字体 
		char name[32];
	public:
		bool get_flag(bool del_flag) {
			if (clicked_flag) {
				if (del_flag)clicked_flag=0;
				return 1;
			} else return 0;
		}
		void del_flag() {
			clicked_flag=0;
		}
		void update() {
			state=0;
			if (is_inside(mx,my,x,y,x+w,y+h)) {
				clicked_flag|=is_pressed;
				state=1;
				if (KEY_DOWN(VK_LBUTTON))state=2;
			}
		}
		int getstate() {
			return state;
		}
		void set_name(const char* str) {
			memset(name,0,32);
			strcpy(name,str);
		}
		void set_xy(int nx,int ny) {
			x=nx,y=ny;
		};
		void set_wh(int nw,int nh) {
			w=nw,h=nh;
		}
		void init() {
			clicked_flag=0;
			memset(name,0,32);
			strcpy(name,"Button");
			x=20,y=20;
			w=80,h=20;
			color1=0xffffff;
			color2=0x000000;
			color3=0x007700;
			color4=0x00ff00;
			color5=0xeeeeee;
		}
		void draw() {
			switch (state) {
				case 0:setfillcolor(color2);break;
				case 1:setfillcolor(color3);break;
				case 2:setfillcolor(color4);break;
			}
			bar(x,y,x+w,y+h);
			setcolor(color1);
			line(x,y,x+w+1,y);
			line(x,y+h,x+w+1,y+h);
			line(x,y,x,y+h+1);
			line(x+w,y,x+w,y+h+1);
			setfont(16,0,"PMingLiU");
			setcolor(color5);
			xyprintf(x+1,y+1,"%s",name);
		}
};
class SWITCH {
	private:
		int x;
		int y;
		int w;
		int h;
		char name[32];
		bool* pstate;
		int color;
	public:
		bool set_p_state(bool *st) {
			pstate=st;
		}
		void set_state(bool nstate) {
			*pstate=nstate;
		}
		void set_xy(int nx,int ny) {
			x=nx,y=ny;
		}
		void set_name(const char* str) {
			memset(name,0,32);
			strcpy(name,str);
		}
		void set_color(int ncolor) {
			color=ncolor;
		}
		void update() {
			if (is_inside(mx,my,x,y,x+w,y+h)) {
				*pstate^=is_release;
			}
		}
		void init() {
			x=16;
			y=16;
			w=16;
			h=16;
			//*pstate=0;
			color=0xcc0000;
			strcpy(name,"switched on lotuz");
		}
		void draw() {
			setfillcolor(color);
			if (*pstate==0)setfillcolor(0x000000);
			bar(x,y,x+w,y+h);
			setcolor(0xffffff);
			line(x,y,x+w+1,y);
			line(x,y+h,x+w+1,y+h);
			line(x,y,x,y+h+1);
			line(x+w,y,x+w,y+h+1);
			setcolor(0xcccccc);
			xyprintf(x+18,y,"%s",name);
		}
};


#endif
