#include <iostream>
#include <chrono>
#include <thread>

#include "CommandExecutorFromPrompt.h"

const std::string EXIT_COMMAND = "exit";

void CommandExecutorFromPrompt::executeCommand()
{
  using namespace std::chrono_literals;

  while (true)
  {
    std::string command;
    std::cout << "[CommandExecutor] Please type your command and ENTER" <<std::endl;
    std::getline(std::cin, command);

    if (command == EXIT_COMMAND)
      return;

    if (command.size() > 0)
    {
      sendCommand(command);

      std::this_thread::sleep_for(1s);

      checkError();
    }
  }
}
