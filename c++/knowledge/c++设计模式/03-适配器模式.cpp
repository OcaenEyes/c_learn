/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-18 13:35:34
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-18 13:57:18
 * @FilePath: /c++/knowledge/c++设计模式/03-适配器模式.cpp
 * @Description: 注释信息
 */

// 适配器模式： 让不兼容的接口可以在一起工作

#include <iostream>

// VGA接口的电脑
class VGA
{
public:
    virtual void play() = 0;
    std::string get_type() const { return "VGA"; }
};

// TV01投影仪 也是VGA接口
class TV01 : public VGA
{
public:
    void play()
    {
        std::cout << "TV01类，通过VGA接口链接投影仪，进行视频播放\n";
    }
};

// 实现一个电脑类
class Computer
{
public:
    // 由于电脑仅支持VGA接口，所以该方法的参数也只能支持VGA接口的指针 或引用
    void play_video(VGA *pVGA)
    {
        pVGA->play();
    }
};

// HDMI接口
class HDMI
{
public:
    virtual void play() = 0;
    std::string get_type() const { return "HDMI"; }
};

/**
 * 方法一： 换一个支持HDMI的接口电脑， 这就叫代码重构
 * 方法二：提供转接头（适配器），把VGA转换为HDMI， 这就叫添加适配器
 *
 */

// 采购了一批新的投影仪，但仅支持HDMI接口
class TV02 : public HDMI
{
    void play()
    {
        std::cout << "TV02类，通过HDMI接口链接投影仪，进行视频播放\n";
    }
};

// 由于电脑 和投影仪无法直链， 故需要适配器类
class VGAToHDMIAdapter : public VGA
{
public:
    VGAToHDMIAdapter(HDMI *p) : p_HDMI(p) {}

    void play()
    { // 该方法 就相当于转换头， 做不同接口的信号转换
        p_HDMI->play();
    }

private:
    HDMI *p_HDMI;
};

int main()
{
    Computer cpu;
    cpu.play_video(new TV01());

    cpu.play_video(new VGAToHDMIAdapter(new TV02()));
    return 0;
}