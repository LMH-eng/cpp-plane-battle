#include"FoeList.h"
#include<typeinfo>
using namespace std;
#include"FoeBig.h"
#include"FoeMid.h"
#include"FoeSma.h"
#include"../Config/Config.h"
FoeList::FoeList(){}
FoeList::~FoeList(){
	for (Foe* p : m_listFoe)
	{
		delete p;
	}
	for (Foe* p : m_listBoomFoe)
	{
		delete p;
	}
}
void FoeList::showAll(){
	for (Foe* p : m_listFoe)
	{
		p->show();
	}
	for (Foe* p : m_listBoomFoe)
	{
      		p->show();
	}
}
/*it 是迭代器，指向链表节点，节点里装的是 Foe*（敌机指针）；
第一次解引用 *it：拿到链表节点里的 Foe* 指针（还不是真实对象）；
第二次解引用 **it：拿到指针指向的真实敌机对象，typeid 才能识别它是小 / 中 / 大敌机。*/

//void FoeList::moveAll(){
//	list<Foe*>::iterator it = m_listFoe.begin();
//	while (it != m_listFoe.end())
//	{//typeid（表达式/类型/变量）返回信息包含类型结果
//		if (typeid(**it) == typeid(FoeSma)) {
//			(*it)->move(8);
//		}
//		else if (typeid(**it) == typeid(FoeMid)) {
//			(*it)->move(6);//（*it）=（Foe*）
//		}
//		else if (typeid(**it) == typeid(FoeBig)) {
//			(*it)->move(4);
//		}
//		if ((*it)->m_y >= BACK_H)
//		{
//			delete(*it);
//			(*it) = nullptr;
//			it = m_listFoe.erase(it);
//			continue;
//		}
//		it++;
//		}
//}
void FoeList::moveAll() {
    auto it = m_listFoe.begin();
    while (it != m_listFoe.end())
    {
        // 1. 按敌机类型设置移动速度（保留你的核心逻辑）
        if (typeid(**it) == typeid(FoeSma)) {
            (*it)->move(8);
        }
        else if (typeid(**it) == typeid(FoeMid)) {
            (*it)->move(6);
        }
        else if (typeid(**it) == typeid(FoeBig)) {
            (*it)->move(4);
        }

        // 2. 检测是否超出屏幕底部（修复迭代器逻辑）
        if ((*it)->m_y >= BACK_H) {
            delete(*it);       // 释放敌机内存
            // 删掉 (*it) = nullptr（多余且可能导致问题）
            it = m_listFoe.erase(it); // erase返回下一个有效迭代器
            // 删掉 continue（用erase返回的迭代器自然处理，无需continue）
        }
        else {
            ++it; // 未删除时，迭代器手动后移
        }
    }
}
void FoeList::notifyShow()
{
	showAll();
}
