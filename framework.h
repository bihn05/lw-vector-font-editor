#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <graphics.h>
#include <iostream>
#include <windows.h>
#include "interact.h"
#include "data.h"

using namespace std;
using namespace ege;

int mode=0;
int select_bujan=0;
int select_bihua=0;
int select_lujng=0;
PT hanzipos_main;
HANZI *process_hanzi;
BUJAN *process_bujan;
BIHUA *process_bihua;
LUJNG *process_lujng;
BUTTON but1;
BUTTON but2;
BUTTON but3;
BUTTON but4;
BUTTON but5;
BUTTON but6;
BUTTON but7;
BUTTON but8;
BUTTON but9;
BUTTON but10;
BUTTON but11;
BUTTON but12;
BUTTON but13;
BUTTON but14;
BUTTON but15;
SWITCH swt1;

void init_object() {
	process_bujan=&process_hanzi->buj[select_bujan];
	process_bihua=&process_bujan->bih[select_bihua];
	process_lujng=&process_bihua->luj[select_lujng];
	but1.init();
	but1.set_name("改为指针");
	but1.set_xy(1,530);
	but1.set_wh(66,18);
	but2.init();
	but2.set_name("编辑该点");
	but2.set_xy(1+68,530);
	but2.set_wh(66,18);
	
	but3.init();
	but3.set_name("上一部件");
	but3.set_xy(1,530+20);
	but3.set_wh(66,18);
	but4.init();
	but4.set_name("下一部件");
	but4.set_xy(1,530+20*2);
	but4.set_wh(66,18);
	
	but5.init();
	but5.set_name("上一笔画");
	but5.set_xy(1+68,530+20);
	but5.set_wh(66,18);
	but6.init();
	but6.set_name("下一笔画");
	but6.set_xy(1+68,530+20*2);
	but6.set_wh(66,18);
	
	but7.init();
	but7.set_name("上一锚点");
	but7.set_xy(1+68*2,530+20);
	but7.set_wh(66,18);
	but8.init();
	but8.set_name("下一锚点");
	but8.set_xy(1+68*2,530+20*2);
	but8.set_wh(66,18);
	
	swt1.init();
	swt1.set_xy(1+68*2,530);
	swt1.set_name("调制");
	swt1.set_p_state(&process_lujng->m);
	
	but9.init();
	but9.set_name("标题文字");
	but9.set_xy(188,530);
	but9.set_wh(66,18);
	
	but10.init();
	but10.set_name("新建部件");
	but10.set_xy(1+68*3,530+20);
	but10.set_wh(66,18);
	but11.init();
	but11.set_name("删除部件");
	but11.set_xy(1+68*3,530+20*2);
	but11.set_wh(66,18);
	
	but12.init();
	but12.set_name("新建笔画");
	but12.set_xy(1+68*4,530+20);
	but12.set_wh(66,18);
	but13.init();
	but13.set_name("删除笔画");
	but13.set_xy(1+68*4,530+20*2);
	but13.set_wh(66,18);
	
	but14.init();
	but14.set_name("新建锚点");
	but14.set_xy(1+68*5,530+20);
	but14.set_wh(66,18);
	but15.init();
	but15.set_name("删除锚点");
	but15.set_xy(1+68*5,530+20*2);
	but15.set_wh(66,18);
}
void global_update() {
	but1.update();
	but2.update();
	but3.update();
	but4.update();
	but5.update();
	but6.update();
	but7.update();
	but8.update();
	but9.update();
	but10.update();
	but11.update();
	but12.update();
	but13.update();
	but14.update();
	but15.update();
	swt1.update();
}
void global_draw() {
	but1.draw();
	but2.draw();
	but3.draw();
	but4.draw();
	but5.draw();
	but6.draw();
	but7.draw();
	but8.draw();
	but9.draw();
	but10.draw();
	but11.draw();
	but12.draw();
	but13.draw();
	but14.draw();
	but15.draw();
	swt1.draw();
}
void process_clear() {
	memset(&process_hanzi,0,sizeof(process_hanzi));
}
void draw_ui() {
	cleardevice();
	swt1.set_p_state(&process_lujng->m);
	setcolor(0xffffff);
	setfont(16,0,"PMingLiU");
	xyprintf(0,0,"LWFontEditor矢量字體製作器 - v0.2");
	
	xyprintf(0,16,"DBEUG:mousepos=(%d,%d) mode=%d buj=%d bih=%d luj=%d",
	mx,my,mode,select_bujan,select_bihua,select_lujng);
	xyprintf(0,32,"mathpos=(%d,%d) shift=%d",
	tx,ty,KEY_DOWN(VK_SHIFT));
	
	setcolor(0x333333);
	line(256,16,256,528);
	line(0,272,512,272);
	line(0,16,512,528);
	line(512,16,0,528);
	
	setcolor(0xffffff);
	line(0,16,800,16);
	line(512,16,512,600);
	line(0,16+512,512,16+512);
	
	line(512+128,16,512+128,16+128);
	line(512+256,16,512+256,16+128);
	line(512,144,800,144);
	
	process_bujan=&process_hanzi->buj[select_bujan];
	process_bihua=&process_bujan->bih[select_bihua];
	process_lujng=&process_bihua->luj[select_lujng];
	
	process_hanzi->draw_han(hanzipos_main,1,0x00cc00);
	setcolor(0x00ff00);
	circle(256+process_lujng->x,272-process_lujng->y,2);
	
	
	
	global_draw();
	if (but1.get_flag(1))mode=0;
	if (but2.get_flag(1))mode=1;
	if (but3.get_flag(1)) {
		select_bujan--;
		if (KEY_DOWN(VK_SHIFT))select_bujan=0;
	}
	if (but4.get_flag(1)) {
		select_bujan++;
		if (KEY_DOWN(VK_SHIFT))select_bujan=process_hanzi->lgth-1;
	}
	if (but5.get_flag(1)) {
		select_bihua--;
		if (KEY_DOWN(VK_SHIFT))select_bihua=0;
	}
	if (but6.get_flag(1)) {
		select_bihua++;
		if (KEY_DOWN(VK_SHIFT))select_bihua=process_bujan->lgth-1;
	}
	if (but7.get_flag(1)) {
		select_lujng--;
		swt1.set_state(process_lujng->m);
		if (KEY_DOWN(VK_SHIFT))select_lujng=0;
	}
	if (but8.get_flag(1)) {
		select_lujng++;
		swt1.set_state(process_lujng->m);
		if (KEY_DOWN(VK_SHIFT))select_lujng=process_bihua->lgth-1;
	}
	if (but10.get_flag(1))process_hanzi->add_buj();
	if (but11.get_flag(1))process_hanzi->del_buj(select_bujan);
	if (but12.get_flag(1))process_bujan->add_bih();
	if (but13.get_flag(1))process_bujan->del_bih(select_bihua);
	if (but14.get_flag(1))process_bihua->add_luj(select_lujng);
	if (but15.get_flag(1))process_bihua->del_luj(select_lujng);
	
	if (select_bujan<0)select_bujan=0;
	if (select_bujan>=process_hanzi->lgth)select_bujan=process_hanzi->lgth-1;
	if (select_bihua<0)select_bihua=0;
	if (select_bihua>=process_bujan->lgth)select_bihua=process_bujan->lgth-1;
	if (select_lujng<0)select_lujng=0;
	if (select_lujng>=process_bihua->lgth)select_lujng=process_bihua->lgth-1;
	
	if (mode==1 && KEY_DOWN(VK_LBUTTON) && is_inside(msmsg.x,msmsg.y,0,16,512,16+512)) {
		process_lujng->x=tx;
		process_lujng->y=ty;
	}
	
	
	//process_lujng->m=swt1.get_state();
	// point here: 576 80
	
	//if (test_flag)record(hanzi);
}

void edit_list() {
	;
}


#endif
