#include "stdafx.h"

class Server
{
private:
    bool _is_on_service;      //是否正在服务
    std::string _ip;        //绑定ip
    uint16_t _port;      //绑定端口

    boost::asio::io_service *_io;       //io调度器
    boost::asio::io_service::work *_work;       //io worker
    boost::asio::ip::tcp::acceptor *_acceptor;     //连接接收器

public:
    uint64_t _last_statistic_tick;      //上次统计tick
    volatile uint64_t _min_new_connections;     //每分钟接收连接数

public:
    Server(const char *ip, uint16_t port) :
            _is_on_service(true),
            _ip(ip), _port(port),
            _acceptor(NULL),
            _last_statistic_tick(0),
            _min_new_connections(0)
            {
                _io = new boost::asio::io_service;
                _work = new boost::asio::io_service::work(*_io);
            }


    ~Server() {}

    void start_service();

private:
    void try_accept()
    {
        //std::cout << "try accept" << std::endl;
        boost::asio::ip::tcp::socket *socket = new boost::asio::ip::tcp::socket(*_io);
        _acceptor->async_accept(*socket, boost::bind(&Server::on_accepted, this, socket, boost::asio::placeholders::error));
    }

    void on_accepted(boost::asio::ip::tcp::socket *socket, const boost::system::error_code &ec);

    void statistic_calculate()
    {
        std::cout << "_min_new_connections: " << _min_new_connections << std::endl;

        _min_new_connections =0;

        _last_statistic_tick = SttGetTickCount();
    }

};
