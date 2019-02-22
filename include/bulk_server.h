#pragma once

#include <boost/asio.hpp>
#include <iostream>

#include "async.h"

#include "commandManager.h"

namespace ba = boost::asio;

class BulkServer
{
public:
  BulkServer(
    boost::asio::io_service& io_service, 
    short port, 
    const int bulkSize)
    : acceptor(io_service, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), port)),
      socket(io_service),
      commandManager (async::connect(bulkSize))
  {
    do_accept();
  }

  ~BulkServer()
  {
    async::disconnect(commandManager);
  }

private:
  void do_accept()
  {           
    boost::system::error_code ec;
    acceptor.accept(socket, &ec);  
    
    if (!ec)    
      this->do_read_command(std::move(socket));
    else
      std::cout << "Error in accept: " << ec.message() << std::endl;

    this->do_accept();

  }
  void do_read_command(ba::ip::tcp::socket socket)
  {
    boost::system::error_code ec;
    const int length = socket.read_some(ba::buffer(comBuffer, comMaxLen), ec);

    if (!ec)
      //!w check that command is full (ends with '\n')
      async::receive(commandManager, comBuffer, length);
    else
      std::cout << "Error in read: " << ec.message() << std::endl;  
  }


  void do_async_accept()
  {    
    //!w change recurssion to while true
    acceptor.async_accept(socket,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            this->do_read_command(std::move(socket));
          }else{
            std::cout << "Error in Accept: " << ec.message() << std::endl;
          }

          this->do_async_accept();
        });
  }

  void do_async_read_command(ba::ip::tcp::socket socket)
  {
    std::cout << "Start reading";
    socket.async_read_some(
      ba::buffer(comBuffer, comMaxLen), 
      [this](boost::system::error_code ec, std::size_t length)
      {
        if (!ec)
          //!w check that command is full (ends with '\n')
          async::receive(commandManager, comBuffer, length);
        else{
          std::cout << "Error in read: " << ec.message() << std::endl;
        }
      });
  }

  
  ba::ip::tcp::acceptor acceptor;
  ba::ip::tcp::socket socket;
  
  async::handle_t commandManager;
  enum { comMaxLen = 1024 };
  char comBuffer[comMaxLen];
};