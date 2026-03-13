#include"Gunner.h"
#include"../Player/Player.h"
#include"../Config/Config.h"
#include"../FoeList/FoeBig.h"
#include"../FoeList/FoeSma.h"
#include"../FoeList/FoeMid.h"
Gunner::Gunner():m_x(0),m_y(0){}
Gunner::~Gunner(){}
void Gunner::init(Player& player)
{
	m_x = player.m_x + PLAYER_W / 2;
	m_y = player.m_y;
	::loadimage(&m_img, L"./res/res/gunner.jpg");
}
void Gunner::show()
{
	::putimage(m_x, m_y, GUNNER_W, GUNNER_H, &m_img, GUNNER_W, 0, SRCPAINT);
	::putimage(m_x, m_y, GUNNER_W, GUNNER_H, &m_img, 0, 0, SRCAND);
}
void Gunner::move()
{
	m_y -= GUNNER_MOVE_STEP;
}
bool  Gunner::isHitFoe(Foe* pfoe)
{ // 1. 取炮弹中心点坐标（碰撞检测的关键：用中心点判断更精准）
	int x = m_x + GUNNER_W / 2;
	int y = m_y + GUNNER_H / 2;
	// 2. 按敌机类型判断：中心点是否在敌机的矩形范围内
	if (typeid(*pfoe) == typeid(FoeSma))
	{
		if (pfoe->m_x <= x && x <= (pfoe->m_x + FOE_SMA_W) && pfoe->m_y <= y && y <= (pfoe->m_y + FOE_SMA_H))
		{
			return true;
		}
	}
	else if (typeid(*pfoe) == typeid(FoeMid))
	{
		if (pfoe->m_x <= x && x <= (pfoe->m_x + FOE_MID_W) && pfoe->m_y <= y && y <= (pfoe->m_y + FOE_MID_H))
		{
			return true;
		}
	}
	else if (typeid(*pfoe) == typeid(FoeBig))
	{
		if (pfoe->m_x <= x && x <= (pfoe->m_x + FOE_BIG_W) && pfoe->m_y <= y && y <= (pfoe->m_y + FOE_BIG_H))
		{
			return true;
		}
	}
	return false;
}

void Gunner::notifyShow()
{
	show();
}
