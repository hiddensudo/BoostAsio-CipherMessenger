#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/array.hpp>

class Server {
private:  
    void startAccept();

    void handleAccept(const boost::system::error_code& error);
    void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& error);

    void doRead();
    void doWrite(const std::string& msg);

    void writeInTerminal();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

    boost::asio::streambuf readMsg;

    std::string key;
    bool isKeyGenerate;

public:
    Server(boost::asio::io_context& ioContext, int port);
    void start(boost::asio::io_service& io);
};

#endif
