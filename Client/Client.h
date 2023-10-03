#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>

class Client {
private:
    void doConnect(const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void doRead();
    void doWrite(const std::string& msg);

    void handleConnect(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);
    void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred);
    
    void writeInTerminal();
    
    boost::asio::io_context& ioContext_;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::streambuf readMsg;
public:
    Client(boost::asio::io_context& ioContext, const std::string& host, const std::string& port);
    ~Client();

    void start(boost::asio::io_service& io);
};

#endif
