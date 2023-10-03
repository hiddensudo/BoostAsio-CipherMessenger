#include "Client.h"
#include <iostream>

int main() {
    boost::asio::io_service io;
    Client client(io, "127.0.0.1", "3000");
    client.start(io);
    return 0;
}