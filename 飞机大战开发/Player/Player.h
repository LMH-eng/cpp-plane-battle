#pragma once  // 防止头文件重复包含（替代传统的#ifndef）
#include<easyx.h>  // EasyX图形库头文件（绘图、窗口、图片加载都靠它）
#include"../Observer/Observer.h"  // 继承观察者基类
class Gunner;  // 前向声明（避免循环包含，因为Gunner类要用到Player，Player也要用到Gunner）

class Player :public Observer {  // 继承Observer，实现统一绘制接口
public:
    // 成员变量（玩家飞机的核心属性）
    IMAGE m_img;        // 玩家飞机的原图（比如飞机png/jpg）
    IMAGE m_masking;    // 玩家飞机的遮罩图（实现透明贴图，避免图片有白色背景）
    int m_x;            // 飞机的x坐标（屏幕水平位置）
    int m_y;            // 飞机的y坐标（屏幕垂直位置）

    // 成员函数（核心功能）
    void init();               // 初始化（位置、图片加载）
    void show();               // 绘制飞机到屏幕
    void move(int direct);     // 按方向键移动飞机
    Gunner* sendGunner();      // 发射炮弹（创建炮弹对象）
    static Player& getPlayer();// 单例模式：获取唯一的玩家对象
    virtual void notifyShow(); // 观察者接口：统一绘制入口

private:
    // 单例模式的核心：私有化构造/析构/拷贝/移动
    Player();                  // 私有构造（外部不能new Player()）
    ~Player();                 // 私有析构（外部不能delete）
    Player(const  Player&) = delete;  // 禁止拷贝构造（防止复制玩家对象）
    Player(Player&&) = delete;        // 禁止移动构造（同上）
};