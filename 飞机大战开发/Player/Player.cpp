#include"Player.h"
#include"../Config/Config.h"
#include"../GunnerList/Gunner.h"
Player::Player():m_x(0),m_y(0){}
Player::~Player(){}
void Player::init() {
	m_x = (BACK_W - PLAYER_W)/2;
	m_y = BACK_H - PLAYER_H;
	m_img;
	m_masking;
	::loadimage(&m_img, L"./res/res/player.jpg");
	::loadimage(&m_masking, L"./res/res/player_mask.jpg");
}
void Player :: show(){
	//先屏蔽图，位或操作
	::putimage(m_x, m_y, &m_masking, SRCPAINT);
	//原图位与操作
	::putimage(m_x, m_y, &m_img, SRCAND);
}
void Player::move(int direct) {
    // direct是方向键（VK_UP/VK_DOWN/VK_LEFT/VK_RIGHT，Windows系统定义的方向键常量）
    if (direct == VK_UP)  // 向上移动
    {
        // 三元运算符：如果向上移后y坐标≥0，就移；否则停在0（不超出屏幕顶部）
        m_y - PLAYER_MOVE_STEP >= 0 ? m_y -= PLAYER_MOVE_STEP : m_y = 0;
    }
    if (direct == VK_DOWN)  // 向下移动
    {
        // 边界：向下移后y坐标 ≤ 窗口高度-飞机高度（不超出屏幕底部）
        m_y + PLAYER_MOVE_STEP <= (BACK_H - PLAYER_H) ? m_y += PLAYER_MOVE_STEP : m_y = (BACK_H - PLAYER_H);
    }
    if (direct == VK_LEFT)  // 向左移动
    {
        m_x - PLAYER_MOVE_STEP >= 0 ? m_x -= PLAYER_MOVE_STEP : m_x = 0;
    }
    if (direct == VK_RIGHT)  // 向右移动
    {
        m_x + PLAYER_MOVE_STEP <= (BACK_W - PLAYER_W) ? m_x += PLAYER_MOVE_STEP : m_x = (BACK_W - PLAYER_W);
    }
}
Gunner* Player::sendGunner()
{
	Gunner* pgun = new Gunner;
	pgun->init(*this);
	return pgun;
}

Player& Player::getPlayer()
{
	static Player player;
	return player;
	// TODO: 在此处插入 return 语句
}

void Player::notifyShow()
{
	show();
}
