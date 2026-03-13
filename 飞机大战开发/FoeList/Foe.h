#pragma once
#include<easyx.h>
#include"../Player/Player.h"
#include<random>
using namespace std;
class Foe {
public:
	IMAGE m_img;
	int m_x;
	int m_y;
	int m_blood;
	int m_showid;// 敌机显示帧ID（用于多帧动画切换，比如爆炸效果）
	static random_device rd;//静态属于类的就一份
	// 静态随机数（所有敌机共用）
	Foe();
	virtual ~Foe();
	virtual void init() = 0;
	virtual void show() = 0;
	void move(int step);
	virtual bool isHitPlayer(Player& player) = 0;


};