#include "async.h"
#include "commandManager.h"
#include "printHandler.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace async {

  handle_t connect(std::size_t bulk)
  {
      CommandManager* manager = new CommandManager(bulk);
      auto printer = std::make_shared<PrintHandler>();
      manager->subscribe(printer);

      return reinterpret_cast<handle_t>(manager);
  }

  void receive(handle_t handle, const char *data, std::size_t /* size */)
  {
    if(handle == nullptr)
      throw std::logic_error("receive: disconnected handle!");

    CommandManager* manager = reinterpret_cast<CommandManager*>(handle);
    
    std::stringstream input; 
    input << data;
    
    for(std::string command; input >> command; )
      manager->add(std::move(command)); 
  }

  void disconnect(handle_t handle) 
  {
    if(handle == nullptr)
      throw std::logic_error("disconnect: handle have already been disconnected!");
    
    CommandManager* manager = reinterpret_cast<CommandManager*>(handle);
    delete manager;
    manager = nullptr;
  }

}
