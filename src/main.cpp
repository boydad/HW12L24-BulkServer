#include <iostream>
#include <chrono>
#include <thread>

#include "bulk_server.h"


int main(int argc, char* argv[]) {
    if (argc != 3)
    {
      std::cerr << "Usage: bulk_server <port> <bulkSize>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    const int port = std::atoi(argv[1]);
    const int bSize = std::atoi(argv[2]);

    BulkServer server(io_service, port, bSize);

    io_service.run();
}
    