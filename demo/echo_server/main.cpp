#include "stdafx.h"
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/lambda/lambda.hpp>

using boost::asio::ip::tcp;
using namespace std; // For atoi.

int total_conn = 0;

class session
    : public boost::enable_shared_from_this<session>
{
    public:
        session(boost::asio::io_service& io_service)
            : socket_(io_service), _send_len(0)
        {
        }

        tcp::socket& socket()
        {
            return socket_;
        }

        void start()
        {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                    boost::bind(&session::handle_read, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }

    private:
        void handle_read(const boost::system::error_code& error,
                size_t bytes_transferred)
        {
            _send_len += bytes_transferred;
            printf("_send_len: %"PRIu64"\n", static_cast<uint64_t>(_send_len));
            if (!error)
            {
                boost::asio::async_write(socket_,
                        boost::asio::buffer(data_, bytes_transferred),
                        boost::bind(&session::handle_write, shared_from_this(),
                            boost::asio::placeholders::error));
            }
            else
            {
                printf("recv error\n");
            }
        }

        void handle_write(const boost::system::error_code& error)
        {
            if (!error)
            {
                socket_.async_read_some(boost::asio::buffer(data_, max_length),
                        boost::bind(&session::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
            }
            else
            {
                printf("write error\n");
            }
        }

        tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];

        boost::atomics::atomic_uint64_t _send_len;
};

class server
{
    public:
        server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
            acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }

    private:
        void start_accept()
        {
            boost::shared_ptr<session> new_session(new session(io_service_));
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&server::handle_accept, this, new_session,
                        boost::asio::placeholders::error));
        }

        void handle_accept(boost::shared_ptr<session> new_session,
                const boost::system::error_code& error)
        {
            start_accept();

            if (!error)
            {
                std::cout << "total connect =" << ++total_conn <<std::endl;
                new_session->start();
            }
        }

        boost::asio::io_service& io_service_;
        tcp::acceptor acceptor_;
};

void run_loop(boost::asio::io_service *io)
{
    int idle_count = 0;
    while(1)
    {
        if(0 == io->poll())
        {
            if(++idle_count >= 10000)
            {
                SttSleep(1);
                idle_count = 0;
            }
        }
    }
}

void f(){cout << "haha" << endl;}
void g(){cout << "hehe" << endl;}

void run_loop_with_deadline(boost::asio::io_service *io)
{
    boost::asio::deadline_timer *m_deadline = new boost::asio::deadline_timer(*io);
    //m_deadline->async_wait(boost::bind(&f));
    //m_deadline->async_wait(boost::function<void(const boost::system::error_code& ec)>());
    int idle_count = 0;
    while(1)
    {
        //cout << "haha" << endl;
        m_deadline->cancel();
        if(0 == io->poll())
        {
            //if(++idle_count >= 10)
            {
                //m_deadline->async_wait(boost::bind(&f));
                m_deadline->expires_from_now(boost::posix_time::millisec(1000));
                //m_deadline->async_wait(boost::bind(&f));
                //m_deadline->async_wait(boost::bind(&g));
                m_deadline->async_wait(boost::lambda::_1);
                //m_deadline->async_wait();
                io->run_one();
                //SttSleep(1);
                idle_count = 0;
            }
        }
    }
}


int main(int argc, char* argv[])
{
    //cout << boost::thread::hardware_concurrency() << endl;
    /*
    int i = 0;
    (boost::lambda::_1 += 1)(i);
    cout << i << endl;
    */
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        server s(io_service, atoi(argv[1]));

        //io_service.run();
        int thread_num = 1;
        //int thread_num = 0;
        if (argc > 2)
            thread_num = atoi(argv[2]);

        boost::thread_group th_group; 
        for (int i=0; i<thread_num; ++i)
        {
            //th_group.add_thread(new boost::thread(boost::bind(&boost::asio::io_service::run, &io_service)));
            //th_group.add_thread(new boost::thread(boost::bind(&boost::asio::io_service::run_one, &io_service)));
            //th_group.add_thread(new boost::thread(boost::bind(&run_loop, &io_service)));
            th_group.add_thread(new boost::thread(boost::bind(&run_loop_with_deadline, &io_service)));
        }

        //getchar();
        th_group.join_all();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

