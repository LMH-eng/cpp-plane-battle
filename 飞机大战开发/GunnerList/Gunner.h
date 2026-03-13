#pragma once
#include<easyx.h>
//#include"../Player/Player.h"
#include"../FoeList/Foe.h"
#include"../Observer/Observer.h"
class Player;
class Gunner :public Observer {
public:
    IMAGE m_img;        // 炮弹的图片
    int m_x;            // 炮弹x坐标
    int m_y;            // 炮弹y坐标

    // 成员函数：核心功能
    Gunner();           // 构造函数
    ~Gunner();          // 析构函数
    void init(Player& player); // 初始化（关联玩家位置）
    void show();        // 绘制炮弹
    void move();        // 炮弹向上移动
    bool isHitFoe(Foe* pfoe); // 检测是否击中敌机
    virtual void notifyShow(); // 观察者接口（统一绘制）


};