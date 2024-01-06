#include "channel.h"

namespace ocean_muduo
{
    channel::channel(eventloop *loop, int fd) : loop_(loop), fd_(fd), events_(0), revents_(0)
    {
    }

    channel::~channel()
    {
    }

} // namespace ocean_muduo
