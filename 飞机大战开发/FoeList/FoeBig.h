#pragma once
#include"../FoeList/Foe.h"
class FoeBig: public Foe {
public:
	void init();
	void show();
	bool isHitPlayer(Player& player);
};