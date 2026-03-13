#pragma once
#include"Foe.h"
class FoeSma : public Foe {
public:
	void init();
	void show();
	bool isHitPlayer(Player& player);
};