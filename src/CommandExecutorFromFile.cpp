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
	std::string commandName{};
	std::string tempStr{};
	std::vector<std::string> commandNameList{};
	commandListFile.open(m_filename);

	if (commandListFile.is_open())
	{
		while (not commandListFile.eof())
		{
			std::getline(commandListFile, tempStr);
			tempStr[tempStr.size() - 1] = '\0';
			commandNameList.push_back(tempStr);
		}
		commandListFile.close();
	}
	else
	{
		std::cout << "[CommandExecutorFromFile] Cannot open " << m_filename << " - please double check filename\n";
	}

	for (const auto command : commandNameList)
	{
		std::cout << "[CommandExecutorFromFile] Execute " << command << " command\n";

		sendCommand(command);

		std::this_thread::sleep_for(1s);

		auto errorLog = checkError();
		if (errorLog != NO_ERROR)
		{
		  m_errorLogger.logError(errorLog);
		}
	}
}
