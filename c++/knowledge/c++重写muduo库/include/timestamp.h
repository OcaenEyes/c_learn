#pragma once
#include <iostream>

namespace ocean_muduo
{
    class timestamp
    {
    private:
        int64_t micro_seconds_since_epoch_; //
    public:
        timestamp(/* args */);
       explicit timestamp(int64_t micro_seconds_since_epoch); // 避免隐式转换
        ~timestamp();

        static timestamp now();

        std::string to_string() const;
    };

} // namespace ocean_muduo
