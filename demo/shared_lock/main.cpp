#include "stdafx.h"

void lock_shared(boost::shared_mutex &shared_lock)
{
    shared_lock.lock_shared();
}

void lock_upgrade(boost::shared_mutex &shared_lock)
{
    shared_lock.lock_upgrade();
}

void unlock_upgrade_and_lock(boost::shared_mutex &shared_lock)
{
    shared_lock.unlock_upgrade_and_lock();
}

void lock_unshared(boost::shared_mutex &shared_lock)
{
    shared_lock.lock();
}

int main(int argc, char **argv)
{
    boost::shared_mutex shared_lock;
    //lock_shared(shared_lock);
    //cout << "lock shared over" << endl;

    //lock_upgrade(shared_lock);
    //cout << "lock upgrade over" << endl;

    try
    {
        unlock_upgrade_and_lock(shared_lock);
    }
    catch(const std::exception &e)
    {
        cout << e.what() << endl;
    }

    cout << "unlock upgrade and lock over" << endl;

    //lock_unshared(shared_lock);
    //cout << "lock unshared over" << endl;
    return 0;
}
