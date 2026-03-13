#include"Back.h"
#include"../Config/Config.h"
Back::Back():m_x(0),m_y(0){}
Back::~Back(){}
void Back::init() {
	::loadimage(&m_img, L"./res/res/back.jpg");
	m_x = 0;
	m_y = -BACK_H;
}
void Back::show(){
	::putimage(m_x, m_y, &m_img);
}
void Back::move(){
	m_y += BACK_MOVE_STEP;
	//判断是否到临界条件
	if (m_y >= 0)
	{
		m_y = -BACK_H;
	}

}
void Back::notifyShow()
{
	show();
}
