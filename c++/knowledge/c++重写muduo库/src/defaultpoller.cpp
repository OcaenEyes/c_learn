/*
 * @Author: OCEAN.GZY
 * @Date: 2024-01-08 08:10:21
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2024-01-08 08:10:21
 * @FilePath: /c++/knowledge/c++重写muduo库/src/defaultpoller.cpp
 * @Description: 注释信息
 */
#include "poller.h"
#include "epollpoller.h"

#include <stdlib.h>

namespace ocean_muduo
{

    poller *poller::new_default_poller(eventloop *loop)
    {
        if (::getenv("MUDUO_USE_POLL"))
        {
            // 生成poll实例
            return nullptr;
        }
        else
        {
            // 生成eploll实例
            return new epollpoller(loop);
        }
    }

} // namespace ocean_muduo
