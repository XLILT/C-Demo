#include "stdafx.h"
#include <sys/shm.h>

int test_create_shm()
{
    int shm_id = 0;

    try
    {
        shm_id = shmget(IPC_PRIVATE, 1024, 0666);
    }
    catch(std::exception &e)
    {
        cout << e.what() << endl;
    }

    if (shm_id < 0)
    {
        perror("shmget");
    }
    else
    {
        cout << "successfully create segment: " << shm_id << endl;
    }

    system("ipcs");

    return shm_id;
}

void *test_attach_shm(int shm_id)
{
    system("ipcs");

    void *buff = shmat(shm_id, NULL, 0);
    if (buff)
    {
        cout << "successfully attach segment: " << shm_id << ", " << buff << endl;
    }
    else
    {
        perror("shmat");
    }

    system("ipcs");

    return buff;
}

int test_detach_shm(const void *shmaddr)
{
    system("ipcs");

    int ret = shmdt(shmaddr);
    if (0 == ret)
    {
        cout << "successfully detach segment: " << shmaddr << endl;
    }
    else
    {
        perror("shmdt");
    }

    system("ipcs");

    return ret;
}

int test_get_shm(int shm_id, struct shmid_ds *buff)
{
    int ret = shmctl(shm_id, IPC_STAT, buff);
    cout << ret << endl;

    return ret;
}

int test_destroy_shm(int shm_id)
{
    system("ipcs");

    int ret = shmctl(shm_id, IPC_RMID, NULL);
    cout << ret << endl;

    system("ipcs");

    return ret;
}

int main(int argc, char **argv)
{
    //int shm_id = test_create_shm();
    int shm_id = atoi(argv[1]);

    /*
    if (shm_id > 0)
    {
        void *buff = test_attach_shm(shm_id);
        if (buff)
        {
            test_detach_shm(buff);
        }
    }
    */

    test_destroy_shm(shm_id);
    getchar();
    return 0;
}
