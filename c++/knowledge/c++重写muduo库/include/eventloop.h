#pragma once

namespace ocean_muduo
{
    /**
     * @brief 事件循环类， 主要包含 channel、poller(epoll的抽象) 
     * 
     */
    class eventloop
    {
    private:
        /* data */
    public:
        eventloop(/* args */);
        ~eventloop();
    };
    
    eventloop::eventloop(/* args */)
    {
    }
    
    eventloop::~eventloop()
    {
    }
    
} // namespace ocean_muduo
