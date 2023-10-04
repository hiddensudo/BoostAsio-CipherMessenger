#include "Client.h"
#include "OneTimePad.h"

#include <boost/bind.hpp>
#include <iostream>

#include <locale>
#include <codecvt>

Client::Client(boost::asio::io_context& ioc, const std::string& host,
               const std::string& port)
    : ioContext_(ioc), socket_(ioc) {
        this->isKeyGenerate = false;
        boost::asio::ip::tcp::resolver resolver(ioContext_);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, port);
        doConnect(endpoints);
    }

Client::~Client() {
    socket_.close();
}

void Client::handleConnect(const boost::system::error_code& error) {
    if(!error) {
        std::cout << "Client was connected to the server" << std::endl
        << "Enter secret key: " << std::endl;
        std::getline(std::cin, this->key);
        this->isKeyGenerate = true;
        doRead();
    } else {
        std::cout << "Error: " << error << std::endl;
    }
}


void Client::doConnect(const boost::asio::ip::tcp::resolver::results_type& endpoints) {
    boost::asio::async_connect(socket_, endpoints, boost::bind(&Client::handleConnect, this, _1));
}

void Client::handleWrite(const boost::system::error_code& error) {
    if(error) {
        std::cout << "Error: " << error << std::endl;
    }
}

void Client::doWrite(const std::string& msg) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring text = converter.from_bytes(msg);
    std::wstring wkey = converter.from_bytes(this->key);
    OneTimePad otp(text, wkey);
    text = otp.cipher();
    std::string converted_msg = converter.to_bytes(text);
    std::string message = converted_msg + '\n';
    std::cout << "Відправляється повідомлення: " << converted_msg << std::endl;
    boost::asio::async_write(socket_, boost::asio::buffer(message), boost::bind(&Client::handleWrite, this, _1));
}

void Client::writeInTerminal() {
    std::string msg;
    while(true) {
        if(isKeyGenerate) {
            std::getline(std::cin, msg);

            if(msg == "quit") {
                break;
            } else {
                doWrite(msg);
            }
        }
        
    }
}

void Client::handleRead(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        std::istream is(&this->readMsg);
        std::string str;
        std::getline(is, str);
        this->readMsg.consume(bytes_transferred);

        std::cout << "Отримав повідомлення: " << str << std::endl;

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring text = converter.from_bytes(str);
        std::string resultTest = converter.to_bytes(text);
        std::wstring wkey = converter.from_bytes(this->key);
        OneTimePad otp(text, wkey);
        text = otp.decipher();
        std::string result = converter.to_bytes(text);

        std::cout << ">>>" << result << std::endl;

        doRead();
    } else {
        std::cout << error.message() << std::endl;
    }
}

void Client::doRead() {
    boost::asio::async_read_until(this->socket_, this->readMsg, '\n', boost::bind(&Client::handleRead, this, _1, _2));
}

void Client::start(boost::asio::io_service& io) {
    std::thread([&]() { io.run(); }).detach();
    writeInTerminal();
}