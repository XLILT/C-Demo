/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2016, Wuhan Douyu Network Technology Co., Ltd.
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail : xiaolongicx@gmail.com
 *  @date : Thu Feb 28 10:30:20 CST 2017
 *
 *  Revision Notes :
 */

#include <stdint.h>
#include <iostream>
#include "stdafx.h"
#include "cfg.h"
#include "MailMigrator.h"

static bool show_stop = false;

static void show_status(int32_t *uid, const MailMigrator *migrator)
{
    while(!show_stop)
    {
        migrator->show_status();
        std::cout << "going to migrate " << *uid << std::endl;

        SttSleep(60000);
    }

    migrator->show_status();
    std::cout << "going to migrate " << *uid << std::endl;
}

int main(int argc, char **argv)
{
    MailConfig cfg;
    if(!cfg.load_cfg())
    {
        std::cout << "load config file failed" << std::endl;
        return -1;
    }

    MailMigrator migrator(&cfg);

    int32_t uid = cfg.begin_uid;

    boost::thread  thrd(boost::bind(&show_status, &uid, &migrator));

    for (; uid <= cfg.end_uid; ++uid)
    {
        migrator.try_migrate(uid);
    }

    show_stop = true;
    thrd.join();

    std::cout << "migrate over." << std::endl;
    return 0;
}
