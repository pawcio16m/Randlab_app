#pragma once

#include <array>
#include <vector>
#include <string>
#include <regex>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "MessageCommunication.h"
#include "PicturePainter.h"

enum Command
{
	SET_WIDTH = 0,
	SET_HEIGHT,
	DRAW_RECTANGLE,
	DRAW_TRIANGLE,
	RENDER,
	NOT_FOUND
};

const std::string PICTURE_DEFAULT_FILENAME = "picture_default";
constexpr std::size_t COMANDS_SIZE = 5u;
const std::array<std::regex, COMANDS_SIZE> AVAILABLE_COMMANDS =
{
	std::regex("SET_WIDTH([[:space:]]+)([[:digit:]]+[[:space:]]+$)"),
	std::regex("SET_HEIGHT([[:space:]]+)([[:digit:]]+[[:space:]]+$)"),
	std::regex("DRAW_RECTANGLE([[:space:]]+)([[:digit:]]+,){3}[[:digit:]]+[[:space:]]+$"),
	std::regex("DRAW_TRIANGLE([[:space:]]+)([[:digit:]]+,){5}[[:digit:]]+[[:space:]]+$"),
	std::regex("RENDER([[:space:]]+)([a-zA-Z_0-9]*)$")
};

using namespace boost::interprocess;

class CommandHandler
{
public:
	CommandHandler(/*message_queue& errorMsgQueue*/)
  : m_sendingErrorMsgQueue(open_only,
                           ERROR_MSG_QUEUE_NAME.c_str()),
    m_receivedCommandMsgQueue(open_only,
	                            COMMAND_MSG_QUEUE_NAME.c_str())
  {}
	virtual ~CommandHandler() = default;
	void run();

private:
  void handleCommand(std::string);
	Command parseCommand(const std::string&);
	std::vector<int> extractInteger(std::string);
	std::string extractFilename(std::string);
	std::string commandToString(Command);
	void sendError(std::string);

	PicturePainter m_picturePainter{};
	message_queue m_sendingErrorMsgQueue;
	message_queue m_receivedCommandMsgQueue;
};
