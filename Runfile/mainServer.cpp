#include "Server.h"
#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::asio::io_service io;
    Server server(io, 3000);

    std::cout << "Waiting for clients..." << std::endl;

    server.start(io);
    return 0;
}