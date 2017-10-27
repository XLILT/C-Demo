#include "stdafx.h"

class Client
{
private:
    std::string _ip;        //服务ip
    uint16_t _port;      //服务端口

    boost::asio::io_service *_io;       //io调度器
    boost::asio::io_service::work *_work;       //io worker

public:
    Client(const char *ip, uint16_t port) :
            _ip(ip), _port(port)
            {
                _io = new boost::asio::io_service;
                _work = new boost::asio::io_service::work(*_io);
            }

    ~Client() {}

    void start_work();

private:
    boost::asio::ip::tcp::socket *try_connect();

};
