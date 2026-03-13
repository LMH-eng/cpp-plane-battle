#include"FoeBig.h"
#include"../Config/Config.h"
void FoeBig::init()
{
	::loadimage(&m_img, L"./res/res/foebig.jpg");
	m_x = rd() % (BACK_W - FOE_BIG_W + 1);
	m_y = -FOE_BIG_H;
	m_blood = 5;
	m_showid = 4;
}
void FoeBig::show()
{
	::putimage(m_x, m_y, FOE_BIG_W, FOE_BIG_H, &m_img, FOE_BIG_W, (4 - m_showid) * FOE_BIG_H, SRCPAINT);
	::putimage(m_x, m_y, FOE_BIG_W, FOE_BIG_H, &m_img, 0, (4 - m_showid) * FOE_BIG_H, SRCAND);
}
bool FoeBig::isHitPlayer(Player& player) {
	int x1 = player.m_x + PLAYER_W / 2;
	int y1 = player.m_y;
	if (m_x <= x1 && x1 <= (m_x + FOE_BIG_W) && m_y <= y1 && y1 <= (m_y + FOE_BIG_H))
	{
		return true;
	}
	int x2 = player.m_x;
	int y2 = player.m_y + PLAYER_H / 2;
	if (m_x <= x2 && x2 <= (m_x + FOE_BIG_W) && m_y <= y2 && y2<= (m_y + FOE_BIG_H))
	{
		return true;
	}
	int x3 = player.m_x + PLAYER_W;
	int y3 = y2;
	if (m_x <= x3 && x3 <= (m_x + FOE_BIG_W) && m_y <= y3 && y3 <= (m_y + FOE_BIG_H))
	{
		return true;
	}
	return false;
}