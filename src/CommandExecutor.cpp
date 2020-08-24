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
    std::cout << "Sending command " << cmd << std::endl;
    m_sendingCommandMsgQueue.send(cmd.data(), cmd.size(), 0);
  }
  catch (interprocess_exception& e)
  {
      std::cout << e.what( ) << std::endl;
  }
}

std::string CommandExecutor::checkError()
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
      std::cout << "[CommandExecutor] Received msg[" << errorLog << "] with size = " << receivedMsgSize << "\n";
      return errorLog;
    }
  }
  catch (interprocess_exception& e)
  {
    std::cout << e.what( ) << std::endl;
  }
  return NO_ERROR;
}



