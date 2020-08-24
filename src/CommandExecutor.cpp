#include <iostream>
#include <string>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "CommandExecutor.h"
#include "MessageCommunication.h"

using namespace boost::interprocess;

void CommandExecutor::sendCommand(std::string cmd)
{
  try
  {
    if (cmd.size() > 0)
    {
      std::cout << "[CommandExecutor] Sending command[" << cmd << "]\n";
      m_sendingCommandMsgQueue.send(cmd.data(), cmd.size(), 0);
    }
  }
  catch (interprocess_exception& e)
  {
      std::cout << e.what( ) << std::endl;
  }
}

void CommandExecutor::checkError()
{
  std::cout << "[CommandExecutor] Checking error...\n";
  try
  {
    std::string errorLog;
    errorLog.resize(MAX_MSG_SIZE);
    std::size_t receivedMsgSize;
    unsigned msgPrio;
    m_receivedErrorMsgQueue.receive(&errorLog[0], errorLog.size(), receivedMsgSize, msgPrio);
    if (receivedMsgSize > 0)
    {
      errorLog.resize(receivedMsgSize);
      if (errorLog != NO_ERROR)
      {
        std::cout << "[CommandExecutor] Received error[" << errorLog << "] with size = " << receivedMsgSize << "\n";
        m_errorLogger.logError(errorLog);
      }
      else
      {
        std::cout << "[CommandExecutor] No error found\n";
      }
    }
  }
  catch (interprocess_exception& e)
  {
    std::cout << e.what( ) << std::endl;
  }
}
