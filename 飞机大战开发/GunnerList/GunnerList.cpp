#include"GunnerList.h"
#include"../Config/Config.h"
GunnerList::GunnerList(){}
GunnerList::~GunnerList()
{
	for (Gunner* p : m_IstGun)
	{
		delete p;
	}
}
void GunnerList:: showAll()
{
	for (Gunner* p : m_IstGun)
	{
		p->show();
	}
}

void GunnerList::moveAll() {
    // 用auto替代冗长的list<Gunner*>::iterator
    auto it = m_IstGun.begin();
    while (it != m_IstGun.end()) {
        (*it)->move();
        if ((*it)->m_y <= -GUNNER_H) {
            delete (*it);//先销毁内容
            it = m_IstGun.erase(it);//再丢掉容器
        }
        else {
            ++it;
        }
    }
}
void GunnerList::notifyShow()
{
	showAll();
}
//void GunnerList::moveAll() {
//    // 用迭代器遍历链表（因为要删除节点，foreach遍历不支持）
//    list<Gunner*>::iterator it = m_IstGun.begin();
//    while (it != m_IstGun.end()) {
//        // 1. 移动当前炮弹
//        (*it)->move();
//
//        // 2. 判断是否超出屏幕顶部（无效炮弹）
//        if ((*it)->m_y <= -GUNNER_H) {
//            // a. 释放炮弹堆内存
//            delete (*it);
//            (*it) = nullptr; // 置空指针，避免野指针
//            // b. 删除链表节点（erase返回下一个节点的迭代器）
//            it = m_IstGun.erase(it);
//            continue; // 跳过后面的++it，直接处理下一个节点
//        }
//        // 3. 未超出屏幕，迭代器后移
//        ++it;
//    }
//}