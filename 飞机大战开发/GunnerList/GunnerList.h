#pragma once
#include<list>
#include"../Observer/Observer.h"
using namespace std;
#include"Gunner.h"
class GunnerList :public Observer {
public:list<Gunner*>m_IstGun;
	  GunnerList();
	  ~GunnerList();
	  void showAll();
		void moveAll();
		  virtual void notifyShow();
};