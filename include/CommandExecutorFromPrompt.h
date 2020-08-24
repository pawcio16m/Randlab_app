#pragma once

#include <string>

#include "CommandExecutor.h"
#include "ErrorLogger.h"

class CommandExecutorFromPrompt : public CommandExecutor
{
public:
	CommandExecutorFromPrompt()//(boost::interprocess::message_queue& queue)
//	: CommandExecutor(queue)
	{}
	virtual ~CommandExecutorFromPrompt() = default;
	void executeCommand() override;

private:
	ErrorLogger m_errorLogger{};
};
