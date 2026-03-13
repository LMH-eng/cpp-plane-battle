#pragma once
#include"../gameframe/gameframe.h"
#include"../Back/Back.h"
#include"../Player/Player.h"
#include"../GunnerList/GunnerList.h"
#include"../FoeList/FoeList.h"
#include"../FoeList/FacFoe.h"
#include"../Observer/Observer.h"
class PlaneApp:public gameframe {
public:
	list<Observer*>m_lstObserver;
	void pushObserver(Observer* pob);
	void popObserver(Observer* pob);
	void notifyAllShow();
	Back m_back;
	Player &m_player;
	GunnerList m_gunList;
	FoeList m_foeList;
	FacFoe m_facfoe;
	int m_score;
	//int m_hwnd;
public:
	PlaneApp();
	~PlaneApp();
	virtual void initmap()override;//这个虚函数一定重写父类否则报错
	virtual void gameinit();
	virtual void gameclose();
	virtual void gameshow();
	void game_WM_KEYDOWN(WPARAM w);
	void game_WM_TIMER(WPARAM w, LPARAM l);
	void showScore();
};