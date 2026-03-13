#pragma once
#include<list>
#include"../Observer/Observer.h"
using namespace std;
#include"Foe.h"
class FoeList :public Observer {
public:
	list<Foe*>m_listFoe;
	list<Foe*>m_listBoomFoe;
	//分离「活跃敌机」和「爆炸敌机」的生命周期，
	// 避免遍历 / 修改 / 删除时的迭代器失效、逻辑冲突；
	FoeList();
	~FoeList();
	void showAll();
	void moveAll();
	virtual void notifyShow();
};