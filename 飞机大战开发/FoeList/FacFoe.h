#pragma once
#include"Foe.h"
class FacFoe {
public:
	Foe* CreateFoe(const string& type);
	//1. 避免不必要的拷贝，提升性能（& 的核心作用）
	//2. 防止函数内部误修改参数（const 的核心作用）
};