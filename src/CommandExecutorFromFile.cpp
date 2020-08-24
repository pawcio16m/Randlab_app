#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

#include "CommandExecutorFromFile.h"
#include "CommandExecutor.h"

void CommandExecutorFromFile::executeCommand()
{
  using namespace std::chrono_literals;

	std::ifstream commandListFile;
	std::string commandName;
	std::vector<std::string> commandNameList{};
	commandListFile.open(m_filename);

	if (commandListFile.is_open())
	{
		while (std::getline(commandListFile, commandName))
		{
      if (commandName.size() > 0)
      {
        commandName[commandName.size() - 1] = '\0';
        commandName.resize(commandName.size() - 1);
        commandNameList.push_back(commandName);
			}
		}
		commandListFile.close();
	}
	else
	{
		std::cout << "[CommandExecutorFromFile] Cannot open " << m_filename << " - please double check filename\n";
	}

	for (const auto command : commandNameList)
	{
	  if (command.size() > 0)
	  {
      std::cout << "[CommandExecutorFromFile] Execute " << command << " command\n";

      sendCommand(command);

      std::this_thread::sleep_for(1s);

      checkError();
	  }
	}
}
