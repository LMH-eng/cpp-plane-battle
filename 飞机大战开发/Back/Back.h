#pragma once
#include<easyx.h>
#include"../Observer/Observer.h"
class Back :public Observer{
public:
	IMAGE m_img;
	int m_x;
	int m_y;
public:
	Back();
	~Back();
	void init();
	void show();
	void move();
	virtual void notifyShow();
};