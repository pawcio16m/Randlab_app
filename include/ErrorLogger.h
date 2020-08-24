#pragma once

#include <string>

class ErrorLogger
{
public:
  ErrorLogger();
  virtual ~ErrorLogger() = default;
  void logError(std::string);

private:
  std::string errorFilename = "log.txt";
};
