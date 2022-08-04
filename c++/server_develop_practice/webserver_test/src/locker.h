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
public:
    cond(/* args */);
    ~cond();
};

cond::cond(/* args */)
{
}

cond::~cond()
{
}

#endif