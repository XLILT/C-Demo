#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include <boost/asio/io_service.hpp>
#include <boost/function.hpp>

class TaskQueue
{
public:
    TaskQueue() :
        _work(_io_service),
        _size(0)
    {}

    ~TaskQueue()
    {
        _io_service.stop();
    }

    // Adds a task to the work queue.  Call blocks until there is an available thread.
    int QueueTask(const boost::function<void()> &t, const char * src_info = NULL, const char * hint = NULL,
            const int exec_time_limit = -1)
    {
        try
        {
            _io_service.post(t);
            ++_size;
        }
        catch(...)
        {}

        return _size;
    }

    int ProcAllTask()
    {
        boost::system::error_code ec;
        int exec_count = _io_service.poll(ec);

        _size -= exec_count;

        return exec_count;
    }

    int ProcOneTask()
    {
        boost::system::error_code ec;
        int exec_count = _io_service.poll_one(ec);
        _size -= exec_count;

        return exec_count;
    }

    int QueueSize()
    {
        return _size;
    }

private:
    boost::asio::io_service _io_service;
    boost::asio::io_service::work _work;
    int _size;
};

#endif //__TASK_QUEUE_H__
