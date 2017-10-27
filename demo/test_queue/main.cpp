#include "stdafx.h"
#include "task_queue.h"

int g_i = 0;

void add(int i, long thread_id)
{
    cout << thread_id << " add " << i << endl;
    ++g_i;
}

template<class Queue>
void post_task(int task_count, Queue *queue)
{
   for(int i = 0; i < task_count; ++i)
   {
        TaskRunCallback cb = boost::bind(&add, i, pthread_self());
        queue->QueueTask(cb);
        //stt_queue->QueueTask(boost::bind(&add));
   }
}

void test_stt_queue(int thread_num, int task_count)
{
    SttTaskQueue stt_queue;
    boost::thread_group thr_group;
    for(int i = 0; i < thread_num; ++i)
    {
        thr_group.create_thread(boost::bind(&post_task<SttTaskQueue>, task_count, &stt_queue));
    }

    uint64_t start_tick = SttGetTickCount();
    //int i  = 0;
    while(g_i < thread_num * task_count)
    {
        int exec_cnt = 0;
        exec_cnt = stt_queue.ProcAllTask();
        //cout << ++i << ", " << exec_cnt << ", " << g_i << endl;
    }

    printf("stt queue %d threads %d tasks const %lums\n", thread_num, task_count, SttGetTickCount() - start_tick);
}

void test_queue(int thread_num, int task_count)
{
    TaskQueue queue;
    boost::thread_group thr_group;
    for(int i = 0; i < thread_num; ++i)
    {
        thr_group.create_thread(boost::bind(&post_task<TaskQueue>, task_count, &queue));
    }

    uint64_t start_tick = SttGetTickCount();
    //int i  = 0;
    while(g_i < thread_num * task_count)
    {
        int exec_cnt = 0;
        exec_cnt = queue.ProcAllTask();
        //cout << ++i << ", " << exec_cnt << ", " << g_i << endl;
    }

    printf("queue %d threads %d tasks const %lums\n", thread_num, task_count, SttGetTickCount() - start_tick);
}

void test_run_sync(int num)
{
    uint64_t start_tick = SttGetTickCount();
    for(int i = 0; i < num; ++i)
    {}

    printf("run sync %d tasks const %lums\n", num, SttGetTickCount() - start_tick);
}

int main(int argc, char **argv)
{
    int thread_num = argc > 1 ? atoi(argv[1]) : 1;
    int task_count = argc > 2 ? atoi(argv[2]) : 1;

    //g_i = 0;
    //test_stt_queue(thread_num, task_count);

    g_i = 0;
    test_queue(thread_num, task_count);

    g_i = 0;
    test_run_sync(thread_num * task_count);

    return 0;
}
