#include "poller.h"

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
            return nullptr;
        }
    }

} // namespace ocean_muduo
