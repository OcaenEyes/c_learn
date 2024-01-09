#include "eventloop_thread_pool.h"
#include "eventloop_thread.h"

namespace ocean_muduo
{

    eventloop_thread_pool::eventloop_thread_pool(eventloop *base_loop, const std::string &name)
        : base_loop_(base_loop),
          name_(name),
          started_(false),
          num_threads_(0),
          next_(0)
    {
    }

    eventloop_thread_pool::~eventloop_thread_pool()
    {
    }

    void eventloop_thread_pool::set_thread_num(int num)
    {
        num_threads_ = num;
    }

    void eventloop_thread_pool::start(const std::function<void(eventloop *)> &cb)
    {
        started_ = true;

        for (int i = 0; i < num_threads_; i++)
        {
            char buf[name_.size() + 32];
            snprintf(buf, sizeof(buf), "%s%d", name_.c_str(), i);
            eventloop_thread *t = new eventloop_thread(cb, buf);
            threads_.push_back(std::unique_ptr<eventloop_thread>(t));
        }
        if (num_threads_ == 0 && cb)
        {
            cb(base_loop_);
        }
    }

    // 如果工作在多线程中， base_loop_默认以轮询的方式分配channel给subloop
    eventloop *eventloop_thread_pool::get_next_loop()
    {
        eventloop *loop = base_loop_;
        if (!loops_.empty())
        {
            loop = loops_[next_];
            ++next_;
            if (next_ >= loops_.size())
            {
                next_ = 0;
            }
        }
        return loop;
    }

    std::vector<eventloop *> eventloop_thread_pool::get_all_loops()
    {
        if (loops_.empty())
        {
            return std::vector<eventloop *>(1, base_loop_);
        }
        else
        {
            return loops_;
        }
    }

    bool eventloop_thread_pool::started() const
    {
        return started_;
    }

    const std::string eventloop_thread_pool::get_name() const
    {
        return name_;
    }

} // namespace ocean_muduo
