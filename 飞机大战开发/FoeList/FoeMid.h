#pragma once
#include"../FoeList/Foe.h"
class FoeMid : public Foe {
public:
	void init();
	void show();
	bool isHitPlayer(Player& player);
};