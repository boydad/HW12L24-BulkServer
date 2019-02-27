#include <iostream>
#include <chrono>
#include <thread>

// #include "async.h"
#include "bulk_server.h"


int main(int argc, char* argv[]) {
  // try
  // {
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
  // }
  // catch (std::exception& e)
  // {
  //   std::cerr << "Exception: " << e.what() << "\n";
  // }    
}
    