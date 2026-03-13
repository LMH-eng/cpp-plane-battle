#pragma once
#include<easyx.h>
#include<conio.h>
#include<map>
#include<windowsx.h>
using namespace std;
#define EX_MOUSE 1
#define EX_KEY 2
#define EX_CHAR 4
#define EX_WINDOW 8
//#define GWL_WNDPROC -4
class gameframe;
extern gameframe* pp;
//窗口回调函数
LRESULT onrun(HWND hwnd, UINT msg, WPARAM w, LPARAM l);

#define ADDMSGMAP(MSGID,MSGTYPE,CLASS)\
        msqmap[MSGID].msqtype = MSGTYPE;\
		msqmap[MSGID].pfun##MSGTYPE =(PFUN##MSGTYPE) &CLASS::game_##MSGID;
class gameframe {
friend LRESULT onrun(HWND hwnd, UINT msg, WPARAM w, LPARAM l);
protected:
	HWND mhwnd;//窗口句柄
	bool mquit;
	using PFUNEX_MOUSE = void (gameframe::* )(int x, int y);
	using  PFUNEX_KEY = void (gameframe::*)(WPARAM w);
	using PFUNEX_WINDOW = void (gameframe::* )(WPARAM, LPARAM);
	struct msqtypefun {
		int msqtype;//描述消息的类别
		union {
			PFUNEX_MOUSE pfunEX_MOUSE;
			PFUNEX_KEY pfunEX_KEY;
			PFUNEX_WINDOW pfunEX_WINDOW;
		};
	};
	map<UINT, msqtypefun>msqmap;//消息映射表 通过宏将不同的信息与对应的处理函数关联起来
public:
	bool getmquit() const { return mquit; }
	gameframe():mquit(false) {

	}
	virtual ~gameframe() {

	}
	virtual void initmap() = 0; 
	//具体业务逻辑的初始化
	void oninit(int w, int h, const TCHAR* ptitle)
	{
		mhwnd = ::initgraph(w, h);//创建窗口
		::setbkcolor(RGB(255, 255, 255));
		::cleardevice();
		//设定窗口标题
		::SetWindowText(mhwnd, ptitle);
		ADDMSGMAP(WM_CLOSE, EX_WINDOW,gameframe)
	    ADDMSGMAP(WM_PAINT, EX_WINDOW,gameframe)
		initmap();
		/*msqmap[WM_LBUTTONDOWN].msqtype = EX_MOUSE;
		msqmap[WM_LBUTTONDOWN].pfunEX_MOUSE = &gameframe::game_WM_LBUTTONDOWN;

		msqmap[WM_KEYDOWN].msqtype = EX_KEY;
		msqmap[WM_KEYDOWN].pfunEX_KEY = &gameframe::game_WM_KEYDOWN;
		msqmap[WM_CLOSE].msqtype = EX_KEY;
		msqmap[WM_CLOSE].pfunEX_WINDOW = &gameframe::gameWM_CLOSE;
		msqmap[WM_PAINT].msqtype = EX_KEY;
		msqmap[WM_PAINT].pfunEX_WINDOW = &gameframe::gameWM_PAINT;*/
		//设定窗口的回调函数
		::SetWindowLong(mhwnd, GWL_WNDPROC, (long)::onrun);//设定回调函数的属性
		//具体游戏代码 
		gameinit();
	}
	//关闭游戏
	void game_WM_CLOSE(WPARAM , LPARAM )
	{//调用具体游戏的关闭窗口
		gameclose();
		::closegraph();//关闭窗口
		mquit = true;
	}
	//显示重绘
	void game_WM_PAINT(WPARAM , LPARAM )
	{
		::BeginBatchDraw();
		//重绘之前先清空一下
		::cleardevice();
		gameshow();
		::EndBatchDraw();
	}
	//接口函数
	virtual void gameinit() = 0;
	virtual void gameclose() = 0;
	virtual void gameshow() = 0;
	/*virtual void game_WM_LBUTTONDOWN(int x, int y) {
		int a = 0;
	}
	virtual void game_WM_KEYDOWN(WPARAM w) {
		int a = 0;
	}*/
	
};
//hwnd窗口句柄
//msg消息ID
// WPARAM w, LPARAM l消息携带的一些参数
extern gameframe* pp;
//LRESULT onrun(HWND hwnd, UINT msg, WPARAM w, LPARAM l); 
#define CREAT(cla)\
gameframe* creat(){\
	return new cla;\
}
#define PAT(w,h,t)\
int width=w;\
int height=h;\
const TCHAR* title=t;
/*
游戏壳的文件:
GameFrame.cpp 公两个文件，需要放入到自己的工程中，GameFrame .h
定义具体游戏的子类，继承游戏壳父类 Gamerrame在具体的子类游戏中 ，重写4个纯虚函数
virtual void game init();
virtual void qame close();
virtual void qame show();
virtual void initMsgMap();
其中 initMsgMap添加消息映射的函数，使用宏 ADDMSGMAP 去添加自己需要的额外的消息绑定ADDMSGMAP(消息ID,消息所属的类别，子类类名)举例:如想添加 鼠标左键按下的消息绑定。其中消息ID :WM LBUTTONDOWN
写法如下:
ADDMSGMAP(WM LBUTTONDOWN，EX MOUSE,子类类名)
还要增加消息对应的处理函数，格式:game 消息ID宏名字比如 鼠标左键按下函数名:qame WM LBUTTONDOWN返回类型为void，参数要根据消息所属的类别而定鼠标类别:EX MOUSE ->(int x int y)EX KEY >(WPARAM w)EX WINDOW->(WPARAM W，LPARAM 1)
在子类的源文件中使用 宏 CREATE_OBJECT(子类类名)
WND_PARAM(窗口的宽度，高度，标题)*/

