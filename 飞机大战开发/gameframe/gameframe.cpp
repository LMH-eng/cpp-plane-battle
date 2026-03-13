#include"gameframe.h"
gameframe* pp = nullptr;
gameframe* creat();
extern int width;
extern int height;
extern const TCHAR* title;
int main()
{
	pp =creat();
	pp->oninit(width, height, title);
	pp->game_WM_PAINT(0,0);
	while (!(pp->getmquit()))
	{
		Sleep(1000);
	}
	delete pp;
	pp = nullptr;
	return 0;
}
  

LRESULT onrun(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
	if (pp->msqmap.count(msg)) {
		switch (pp->msqmap[msg].msqtype)
		{
		case EX_MOUSE:
		{
			int x = GET_X_LPARAM(1);
			int y = GET_Y_LPARAM(1);
			(pp->*pp->msqmap[msg].pfunEX_MOUSE)(x, y);
		}
		break;
		case EX_KEY:
		{
			(pp->*pp->msqmap[msg].pfunEX_KEY)(w);
		}
		break;
		case EX_WINDOW:
		{
			(pp->*pp->msqmap[msg].pfunEX_WINDOW)(w, l);
		}
		break;
		}
	}

	//设置无效区
	RECT rect{ 0, 0, 666, 666 };
	::InvalidateRect(pp->mhwnd, &rect, FALSE);//画面改动后，手动调用「触发重绘
	return ::DefWindowProc(hwnd, msg, w, l);//默认的回调函数，对于不关心的消息交给他处理
}