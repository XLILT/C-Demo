#include "Server.h"

static const std::size_t BUF_LEN = 3 * 1024;

static const char *buf;

void Server::start_service()
{
    buf = new char[BUF_LEN];

    try
    {
        _acceptor  = new boost::asio::ip::tcp::acceptor(*_io);
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), _port);
        //boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::address(boost::asio::ip::address_v4::from_string("192.168.91.132")), _port);
        _acceptor->open(endpoint.protocol());
        _acceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        _acceptor->bind(endpoint);
        _acceptor->listen();

        try_accept();
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    uint16_t idle_count = 0;
    uint64_t asio_count = 0;

    while(_is_on_service)
    {
        idle_count = 0;
        asio_count = 0;

        try
        {
            asio_count = _io->poll();
        }
        catch(std::exception &e)
        {
            _io->reset();
        }

        if(asio_count == 0)
        {
            idle_count++;
        }
        else
        {
            idle_count = 0;
        }

        if (idle_count >= 0)
        {
            struct timespec req = {0};
            struct timespec rem = {0};
            req.tv_sec = 0;     /*秒*/
            //req.tv_nsec = (1) * 1000000L;    /*纳秒*/
            req.tv_nsec = 10000000;    /*纳秒*/
            nanosleep(&req, &rem);
        }

        if (SttGetTickCount() > _last_statistic_tick + 60 * 1000)
        {
            if (_last_statistic_tick == 0)
            {
                //需要初始化_last_statistic_tick
                _last_statistic_tick = SttGetTickCount();
            }
            else
            {
                statistic_calculate();
            }
        }
    }
}

void Server::on_accepted(boost::asio::ip::tcp::socket *socket, const boost::system::error_code &ec)
{
    //std::cout << "on accept" << std::endl;
    _min_new_connections++;

    try
    {
        socket->send(boost::asio::buffer(buf, BUF_LEN));

        socket->close();
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    delete socket;

    try_accept();
}
