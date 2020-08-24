#include <iostream>
#include <chrono>
#include <thread>

#include "CommandExecutorFromPrompt.h"

void CommandExecutorFromPrompt::executeCommand()
{
  using namespace std::chrono_literals;

  while (true)
  {
    std::string command;
    std::cout << "[CommandExecutor] Please type your command and ENTER" <<std::endl;
    std::getline(std::cin, command);

    sendCommand(command);

    std::this_thread::sleep_for(1s);

    auto errorLog = checkError();
    if (errorLog != NO_ERROR)
    {
      m_errorLogger.logError(errorLog);
    }
  }
}
