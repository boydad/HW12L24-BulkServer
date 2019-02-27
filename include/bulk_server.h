#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

#include "async.h"

namespace ba = boost::asio;


class session
  : public std::enable_shared_from_this<session>
{
public:
  session(
    ba::ip::tcp::socket socket,
    async::handle_t& commandManager
    ) :
      socket(std::move(socket)), 
      commandManager(commandManager)
  {
  }


  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(this->shared_from_this());
    socket.async_read_some(
        ba::buffer(comBuffer, comMaxLen), 
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec) {
            //!w check that command is full (ends with '\n')
            async::receive(commandManager, comBuffer, length);
            this->do_read();
          }
        });
  }

  ba::ip::tcp::socket socket;
  enum { comMaxLen = 1024 };
  char comBuffer[comMaxLen];
  async::handle_t& commandManager;

};


class BulkServer
{
public:
  BulkServer(
    boost::asio::io_service& io_service, 
    short port, 
    const int bulkSize
    ) :
      acceptor(io_service, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), port)),
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
    acceptor.async_accept(socket,
      [this](boost::system::error_code ec)
      {
        if (!ec)
          std::make_shared<session>(std::move(socket), commandManager)->start();

        do_accept();
      });
  }
  
  ba::ip::tcp::acceptor acceptor;
  ba::ip::tcp::socket socket;
  
  async::handle_t commandManager;
};