#include"PlaneApp.h"
#include"../FoeList/FoeBig.h"
#include"../FoeList/FoeMid.h"
#include"../FoeList/FoeSma.h"
#include"../Config/Config.h"
CREAT(PlaneApp)
PAT(600,800,L"飞机大战")
PlaneApp::PlaneApp():m_player(Player::getPlayer()){}
PlaneApp::~PlaneApp(){}
void PlaneApp::pushObserver(Observer* pob)
{
	m_lstObserver.push_back(pob);
}
void PlaneApp::popObserver(Observer* pob)
{
	auto it = m_lstObserver.begin();
	while (it != m_lstObserver.end())
	{
		if (*it == pob)
		{
			it = m_lstObserver.erase(it);
			break;
		}
		++it;
	}
}
void PlaneApp::notifyAllShow()
{
	for (Observer* p : m_lstObserver)
	{
		p->notifyShow();
	}
}


void PlaneApp::initmap() {
	ADDMSGMAP (WM_KEYDOWN,EX_KEY,PlaneApp)
	ADDMSGMAP(WM_TIMER, EX_WINDOW, PlaneApp)
		

}//这个虚函数一定重写父类否则报错
 void PlaneApp::gameinit(){
	 m_back.init(); 
	 m_player.init();
	 ::SetTimer(mhwnd, 1/*定时器ID*/, 80/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 ::SetTimer(mhwnd, 2/*定时器ID*/, 20/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 ::SetTimer(mhwnd, 3/*定时器ID*/, 60/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 ::SetTimer(mhwnd, 4/*定时器ID*/, 3000/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 ::SetTimer(mhwnd, 5/*定时器ID*/, 60/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 ::SetTimer(mhwnd, 6/*定时器ID*/, 30/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 ::SetTimer(mhwnd, 7/*定时器ID*/, 250/*触发的频率，亳秒为单位*/, nullptr/*定时器的回调函数*/);
	 pushObserver(&m_back);
	 pushObserver(&m_player);
	 pushObserver(&m_gunList);
	 pushObserver(&m_foeList);

 }
 void PlaneApp::gameclose(){}
 void PlaneApp::gameshow() {
	 notifyAllShow();
	/* m_back.show();
	 m_player.show();
	 m_gunList.showAll();  
	 m_foeList.showAll();*/
	 showScore();
 }
 void PlaneApp::game_WM_KEYDOWN(WPARAM w) {
	 if (w == VK_SPACE)
	 {
		 Gunner* pgun=m_player.sendGunner();
		 m_gunList.m_IstGun.push_back(pgun);
	 }
 }
 void PlaneApp::game_WM_TIMER(WPARAM w, LPARAM l) {
	 if (w == 1)
	 {
		 m_back.move();
	 }
	 else if (w == 2)
	 {
		 if (::GetAsyncKeyState(VK_UP))
		 {
			 m_player.move(VK_UP);
		 }
		 if (::GetAsyncKeyState(VK_DOWN))
		 {
			 m_player.move(VK_DOWN);
		 }
		 if (::GetAsyncKeyState(VK_LEFT))
		 {
			 m_player.move(VK_LEFT);
		 }
		 if (::GetAsyncKeyState(VK_RIGHT))
		 {
			 m_player.move(VK_RIGHT);
		 }
	 }
	 else if (w == 3)
	 {
		 m_gunList.moveAll();
	 }
	 else if (w == 4)
	 {
		 int r = Foe::rd() % 100;
		 Foe* pfoe = nullptr;
		 if (r >= 0 && r <= 50)
		 {
			 pfoe = m_facfoe.CreateFoe(CREATE_FOESMA);

		 }
		 else if (r >= 51 && r <= 80)
		 {
			 pfoe = m_facfoe.CreateFoe(CREATE_FOEMID);
		 }
		 else
		 {
			 pfoe = m_facfoe.CreateFoe(CREATE_FOEBIG);
		 }
		 if (pfoe)
		 {
			 pfoe->init();
			 m_foeList.m_listFoe.push_back(pfoe);
		 }
	 }
	 else if (w == 5)
	 {
		 m_foeList.moveAll();
	 }
	
	 else if (w == 6)
	 {
		// bool isBoom = false;
		 auto itfoe = m_foeList.m_listFoe.begin();
		 while (itfoe != m_foeList.m_listFoe.end())
		 {
			 // 1. 敌机撞玩家：游戏结束（这部分逻辑没问题）
			 if ((*itfoe)->isHitPlayer(m_player))
			 {
				 ::KillTimer(mhwnd, 1);
				 ::KillTimer(mhwnd, 2);
				 ::KillTimer(mhwnd, 3);
				 ::KillTimer(mhwnd, 4);
				 ::KillTimer(mhwnd, 5);
				 ::KillTimer(mhwnd, 6);
				 ::KillTimer(mhwnd, 7);
				 MessageBox(mhwnd, L"游戏结束", L" ", MB_OK);
				 game_WM_CLOSE(0, 0);
				 return;
			 }

			 // 2. 遍历子弹检测击中
			 bool foeDeleted = false; // 新增标记：标记敌机是否被删除
			 auto itgun = m_gunList.m_IstGun.begin();
			 while (itgun != m_gunList.m_IstGun.end())
			 {
				 if ((*itgun)->isHitFoe(*itfoe))
				 {
					 // 2.1 删除击中的子弹（安全写法）
					 delete (*itgun);
					 //(*itgun) = nullptr;
					 itgun = m_gunList.m_IstGun.erase(itgun);

					 // 2.2 扣敌机血量
					 --(*itfoe)->m_blood;
					 if ((*itfoe)->m_blood <= 0)
					 {
						 // 2.3 加分（typeid放在erase前，安全）
						 if (typeid(**itfoe) == typeid(FoeSma)) {
							 m_score += 10; // 小敌机加10分
						 }
						 else if (typeid(**itfoe) == typeid(FoeMid)) {
							 m_score += 30; // 中敌机加30分
						 }
						 else if (typeid(**itfoe) == typeid(FoeBig)) {
							 m_score += 50; // 大敌机加50分
						 }

						 // 2.4 加入爆炸列表 + 删除敌机
						 m_foeList.m_listBoomFoe.push_back(*itfoe);
						 itfoe = m_foeList.m_listFoe.erase(itfoe); // itfoe更新为下一个

						 // 2.5 标记敌机已删除，跳出子弹循环
						 foeDeleted = true;
						// isBoom = true;
						 break; // 跳出子弹循环，不再遍历剩余子弹
					 }
					 continue; // 子弹已删除，跳过++itgun
				 }
				 ++itgun; // 子弹未击中，正常迭代
			 }

			 // 3. 关键：敌机已删除则跳过++itfoe，否则正常迭代
			 if (foeDeleted)
			 {
				 foeDeleted = false; // 重置标记
				 continue; // 跳过下方的isBoom重置和++itfoe
			 }

			 // 4. 未删除敌机时，重置爆炸标记 + 正常迭代
			// if (isBoom) isBoom = false;
			 ++itfoe;
		 }
		 }
	else if (w == 7)
	{
		auto it = m_foeList.m_listBoomFoe.begin();
		while (it != m_foeList.m_listBoomFoe.end())
		{
			
			if (--(*it)->m_showid < 0)
			{
				delete(*it);
					//(*it) = nullptr;
					it = m_foeList.m_listBoomFoe.erase(it);
					continue;
			}
			it++;
		}
	}


}
void PlaneApp::showScore(){
	wstring wstr = L"分数为：";
	//整形转字符串itoa
	TCHAR sc[5] = { 0 };
	_itow_s(m_score, sc, 10);
	wstr+=sc;
	::settextcolor(RGB(10,60,200));
	RECT rect{0,0,100,30};
	::drawtext(wstr.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//水平垂直单行居中显示
}