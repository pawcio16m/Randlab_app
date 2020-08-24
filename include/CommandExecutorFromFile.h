#pragma once

#include <string>

#include "CommandExecutor.h"

class CommandExecutorFromFile : public CommandExecutor
{
public:
	CommandExecutorFromFile(std::string filename)
  : m_filename(filename)
  {}
  virtual ~CommandExecutorFromFile() = default;
  void executeCommand() override;

private:
  std::string m_filename;
};
