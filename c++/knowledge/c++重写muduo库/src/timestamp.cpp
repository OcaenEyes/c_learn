#include "timestamp.h"

#include <time.h>

namespace ocean_muduo
{
    timestamp::timestamp(/* args */) : micro_seconds_since_epoch_(0)
    {
    }

    timestamp::timestamp(int64_t micro_seconds_since_epoch) : micro_seconds_since_epoch_(micro_seconds_since_epoch)
    {
    }

    timestamp::~timestamp()
    {
    }

    timestamp timestamp::now()
    {
        return timestamp(time(nullptr));
    }

    std::string timestamp::to_string() const
    {
        char buf[128] = {0};
        tm *tm_time = localtime(&micro_seconds_since_epoch_);
        snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
                 tm_time->tm_year + 1900,
                 tm_time->tm_mon + 1,
                 tm_time->tm_mday,
                 tm_time->tm_hour,
                 tm_time->tm_min,
                 tm_time->tm_sec);
        return buf;
    }

} // namespace ocean_muduo


