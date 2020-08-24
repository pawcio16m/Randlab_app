#pragma once

#include <string>

#include "CommandExecutor.h"
#include "ErrorLogger.h"

class CommandExecutorFromPrompt : public CommandExecutor
{
public:
	CommandExecutorFromPrompt() = default;
	virtual ~CommandExecutorFromPrompt() = default;
	void executeCommand() override;

private:
	ErrorLogger m_errorLogger{};
};
