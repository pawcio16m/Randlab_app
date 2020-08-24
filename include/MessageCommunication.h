#pragma once

#include <iostream>
#include <string>

const std::string COMMAND_MSG_QUEUE_NAME = "commands_queue";
const std::string ERROR_MSG_QUEUE_NAME = "error_queue";

const std::string NO_ERROR = "ERROR_NOT_OCCUR";

constexpr std::size_t MAX_MSG_SIZE = 100;
constexpr std::size_t MAX_MSG_IN_QUEUE = 1000;
