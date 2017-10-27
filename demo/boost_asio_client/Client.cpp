#include "stdafx.h"
#include "Client.h"

static const std::size_t BUF_LEN = 3 * 1024;

static char *buf;

void Client::start_work()
{
    buf = new char[BUF_LEN];

    while(true)
    {
        boost::asio::ip::tcp::socket *socket = try_connect();

        try
        {
            socket->receive(boost::asio::buffer(buf, BUF_LEN));

            socket->close();
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }

        delete socket;
    }
}

boost::asio::ip::tcp::socket *Client::try_connect()
{
    boost::asio::ip::tcp::socket * socket = new boost::asio::ip::tcp::socket(*_io);

    // open
    socket->open(boost::asio::ip::tcp::v4());

    // connect
    try
    {
        socket->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(_ip.c_str()), _port));
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return socket;
}
