#pragma once

#include <string>

#include <boost/interprocess/ipc/message_queue.hpp>

#include "MessageCommunication.h"

using namespace boost::interprocess;

struct CommandExecutor
{
	CommandExecutor()
	: m_sendingCommandMsgQueue(open_only,
	                           COMMAND_MSG_QUEUE_NAME.c_str()),
	  m_receivedErrorMsgQueue(open_only,
                            ERROR_MSG_QUEUE_NAME.c_str())
	{
	}
	virtual ~CommandExecutor() = default;

	virtual void executeCommand() = 0;

	void sendCommand(std::string);
	std::string checkError();

	message_queue m_sendingCommandMsgQueue;
	message_queue	m_receivedErrorMsgQueue;
};
