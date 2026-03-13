#include"Foe.h"
random_device Foe::rd;
Foe::Foe() {
	
	m_x = m_y = m_blood = m_showid = 0;
}
Foe::~Foe(){}
void Foe::move(int step)
{
	m_y += step;
}