#include "Server.h"
#include "OneTimePad.h"
#include <boost/bind.hpp>
#include <iostream>

#include <locale>
#include <codecvt>

Server::Server(boost::asio::io_service& io_service, int port)
    : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      socket_(io_service) {
    startAccept();
}

void Server::startAccept() {
    acceptor_.async_accept(socket_, [this](const boost::system::error_code& error) {
        if (!error) {
            std::cout << "Client connected: " << this->socket_.remote_endpoint() << std::endl;
            doRead();
        }
        startAccept();
    });
}

void Server::handleRead(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::istream is(&this->readMsg);
        std::string str;
        std::getline(is, str);
        this->readMsg.consume(bytes_transferred);

        std::cout << "Отримав повідомлення: " << str << std::endl;

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring text = converter.from_bytes(str);
        std::string resultTest = converter.to_bytes(text);

        OneTimePad otp(text, L"дота");
        text = otp.decipher();
        std::string result = converter.to_bytes(text);

        std::cout << ">>>" << result << std::endl;

        doRead();
    } else {
        std::cout << error.message() << std::endl;
    }
}

void Server::doRead() {
    boost::asio::async_read_until(this->socket_, this->readMsg, '\n', boost::bind(&Server::handleRead, this, _1, _2));
}

void Server::handleWrite(const boost::system::error_code& error) {
    if(error) {
        std::cout << "Error: " << error << std::endl;
    }
}

void Server::doWrite(const std::string& msg) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring text = converter.from_bytes(msg);

    OneTimePad otp(text, L"дота");
    text = otp.cipher();
    std::string converted_msg = converter.to_bytes(text);

    std::string message = converted_msg + '\n';
    std::cout << "Відправляється повідомлення: " << converted_msg << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(message), boost::bind(&Server::handleWrite, this, _1));
}

void Server::writeInTerminal() {
    std::string msg;
    while(true) {
        std::getline(std::cin, msg);

        if(msg == "quit") {
            break;
        } else {
            doWrite(msg);
        }
    }
}

void Server::start(boost::asio::io_service& io) {
    std::thread([&]() { io.run(); }).detach();
    writeInTerminal();
}