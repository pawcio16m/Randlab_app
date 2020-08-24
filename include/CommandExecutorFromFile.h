#pragma once

#include <string>

#include "CommandExecutor.h"
#include "ErrorLogger.h"

class CommandExecutorFromFile : public CommandExecutor
{
public:
	CommandExecutorFromFile(/*boost::interprocess::message_queue& queue,*/ std::string filename)
  : //CommandExecutor(queue),
	  m_filename(filename)
	{}
	virtual ~CommandExecutorFromFile() = default;
	void executeCommand() override;

private:
	void printCommand(std::string);

	std::string m_filename;
	ErrorLogger m_errorLogger{};
};


