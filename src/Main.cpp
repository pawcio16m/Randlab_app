#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "CommandExecutorFromPrompt.h"
#include "CommandExecutorFromFile.h"
#include "CommandHandler.h"

using namespace boost::interprocess;

int main(int argc, char **argv)
{
  message_queue::remove(COMMAND_MSG_QUEUE_NAME.c_str());
  message_queue::remove(ERROR_MSG_QUEUE_NAME.c_str());

  message_queue sendingCommandMsgQueue(create_only,
                                       COMMAND_MSG_QUEUE_NAME.c_str(),
                                       MAX_MSG_IN_QUEUE,
                                       MAX_MSG_SIZE);
  message_queue sendingErrorMsgQueue(create_only,
                                     ERROR_MSG_QUEUE_NAME.c_str(),
                                     MAX_MSG_IN_QUEUE,
                                     MAX_MSG_SIZE);
  auto pid = fork();

  CommandHandler cmdHandler{};
  std::unique_ptr<CommandExecutor> cmdExecutor;

  if (argc > 1)
  {
    std::string filename = argv[1];
    cmdExecutor = std::make_unique<CommandExecutorFromFile>(filename);
  }
  else
  {
    cmdExecutor = std::make_unique<CommandExecutorFromPrompt>();
  }

  if (pid == 0)
  {
    cmdHandler.run();
  }
  else
  {
    cmdExecutor->executeCommand();
  }
	return 0;
}
