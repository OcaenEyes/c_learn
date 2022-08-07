/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-05 06:19:13
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-05 06:27:11
 * @FilePath: /c++/server_develop_practice/webserver_test/src/locker.h
 * @Description: 注释信息
 */
#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class sem
{
private:
    sem_t m_sem;

public:
    sem(/* args */);
    sem(int num);
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    };
    bool post()
    {
        return sem_post(&m_sem) == 0;
    };
    ~sem();
};

sem::sem(/* args */)
{
    if (sem_init(&m_sem, 0, 0) != 0)
    {
        throw std::exception();
    }
}

sem::sem(int num)
{
    if (sem_init(&m_sem, 0, num) != 0)
    {
        throw std::exception();
    }
}

sem::~sem()
{
    sem_destroy(&m_sem);
}

class locker
{
private:
    pthread_mutex_t m_mutex;

public:
    locker(/* args */);
    ~locker();
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
};

locker::locker(/* args */)
{
    if (pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        throw std::exception();
    }
}

locker::~locker()
{
    pthread_mutex_destroy(&m_mutex);
}

class cond
{
private:
    /* data */
    pthread_cond_t m_cond;

public:
    cond(/* args */);

    bool wait(pthread_mutex_t *m_mutex)
    {
        int ret = 0;
        ret = pthread_cond_wait(&m_cond, m_mutex);
        return ret == 0;
    }

    bool timewait(pthread_mutex_t *m_mutex, struct timespec t)
    {
        int ret = 0;
        ret = pthread_cond_timedwait(&m_cond, m_mutex, &t);
        return ret == 0;
    }

    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast()
    {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

    ~cond();
};

cond::cond(/* args */)
{
    if (pthread_cond_init(&m_cond, NULL) != 0)
    {
        throw std::exception();
    }
}

cond::~cond()
{
    pthread_cond_destroy(&m_cond);
}

#endif