#pragma once

#include <string>

#include "CommandExecutor.h"

class CommandExecutorFromPrompt : public CommandExecutor
{
public:
	CommandExecutorFromPrompt() = default;
	virtual ~CommandExecutorFromPrompt() = default;
	void executeCommand() override;
};
