#include"FoeSma.h"
#include"../Config/Config.h"
void FoeSma::init()
{
	::loadimage(&m_img, L"./res/res/foesma.jpg");
	m_x = rd() % (BACK_W - FOE_SMA_W + 1);
	m_y = -FOE_SMA_H;
	m_blood = 1;
	m_showid = 2;
}
void FoeSma::show()
{
	::putimage(m_x, m_y, FOE_SMA_W, FOE_SMA_H, &m_img, FOE_SMA_W, (2 - m_showid) * FOE_SMA_H, SRCPAINT);
	::putimage(m_x, m_y, FOE_SMA_W, FOE_SMA_H, &m_img, 0, (2 - m_showid) * FOE_SMA_H, SRCAND);
}
bool FoeSma::isHitPlayer(Player& player) {
	int x1 = player.m_x + PLAYER_W / 2;
	int y1 = player.m_y;
	if (m_x <= x1 && x1 <= (m_x + FOE_SMA_W) && m_y <= y1 && y1 <= (m_y + FOE_SMA_H))
	{
		return true;
	}
	int x2 = player.m_x;
	int y2 = player.m_y + PLAYER_H / 2;
	if (m_x <= x2 && x2 <= (m_x + FOE_SMA_W) && m_y <= y2 && y2 <= (m_y + FOE_SMA_H))
	{
		return true;
	}
	int x3 = player.m_x + PLAYER_W;
	int y3 = y2;
	if (m_x <= x3 && x3 <= (m_x + FOE_SMA_W) && m_y <= y3 && y3 <= (m_y + FOE_SMA_H))
	{
		return true;
	}
	return false;
}