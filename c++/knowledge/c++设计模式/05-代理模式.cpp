
/**
 *  代理Proxy模式：通过代理类，来控制实际对象的访问权限
 *  客户        助理proxy【代理类，用于权限控制】       老板 【委托类】
 */

#include <iostream>
#include <memory>

class VideoSite
{
public:
    virtual void free_movie() = 0;
    virtual void vip_movie() = 0;
    virtual void tickt_movie() = 0;
};

class OceanVideoSite : public VideoSite // 委托类
{
public:
    void free_movie()
    {
        std::cout << "观看免费电影\n";
    }
    void vip_movie()
    {
        std::cout << "观看VIP电影\n";
    }
    void tickt_movie()
    {
        std::cout << "用电影票观看电影\n";
    }
};

class OceanVideoSiteProxy : public VideoSite // 代理类 ，代理OceanVideoSite
{
public:
    OceanVideoSiteProxy()
    {
        p_video = new OceanVideoSite();
    }

    ~OceanVideoSiteProxy()
    {
        delete p_video;
        p_video = nullptr;
    }

    void free_movie()
    {
        p_video->free_movie();
    }
    void vip_movie()
    {
        std::cout << "普通用户，无法观看VIP电影\n";
    }
    void tickt_movie()
    {
        std::cout << "普通用户，无法用电影票观看电影\n";
    }

private:
    VideoSite *p_video;
};

int main()
{
    std::unique_ptr<VideoSite> p(new OceanVideoSite());
    p->free_movie();
    p->vip_movie();
    p->tickt_movie();

    std::unique_ptr<VideoSite> p1(new OceanVideoSiteProxy());
    p1->free_movie();
    p1->vip_movie();
    p1->tickt_movie();

    return 0;
}