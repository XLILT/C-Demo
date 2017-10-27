#include "stdafx.h"

void printf_int(int x)
{
    printf("%s: %d\n", __FUNCTION__, x);
}

void printf_int2(boost::asio::io_service *_io, int x)
{
    printf("%s: %d\n", __FUNCTION__, x);

    if (_io)
    {
        //_io->dispatch(boost::bind(printf_int, x+1));
        _io->post(boost::bind(printf_int, x+1));

        printf("%s run over\n", __FUNCTION__);
    }
}

int main(int argc, char **argv)
{
    boost::asio::io_service *_io = new boost::asio::io_service;
    boost::asio::io_service::work *_work = new boost::asio::io_service::work(*_io);

    if (_io)
    {
        _io->dispatch(boost::bind(printf_int2, _io, 1));
    }

    _io->run();

    return 0;
}
