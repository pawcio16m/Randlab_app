#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#include <boost/regex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

#include "CommandHandler.h"
#include "PicturePainter.h"
#include "MessageCommunication.h"

using namespace boost::interprocess;

void CommandHandler::run()
{
  using namespace std::chrono_literals;
  using namespace boost::interprocess;

  while (true)
  {
    std::cout << "[CommandHandler] Waiting for command...\n";
    try
    {
      std::string command;
      command.resize(MAX_MSG_SIZE);
      std::size_t receivedMsgSize;
      unsigned msgPrio;
      m_receivedCommandMsgQueue.receive(&command[0], command.size(), receivedMsgSize, msgPrio);
      if (receivedMsgSize > 0)
      {
        command.resize(receivedMsgSize);
        std::cout << "[CommandHandler] Received msg[" << command << "] with size = " << receivedMsgSize << "\n";
        handleCommand(command);
      }
    }
    catch (interprocess_exception& e)
    {
      std::cout << e.what( ) << std::endl;
    }
  }
}

void CommandHandler::handleCommand(std::string command)
{
	auto res = extractInteger(command);
	auto numbOfIntInCommand = res.size();

	switch (auto cmdType = parseCommand(command))
	{
		case Command::SET_WIDTH:
		{
			if (numbOfIntInCommand == 1)
			{
				m_picturePainter.setWidth(res[0]);
        sendAckStatus();
			}
			else
			{
				std::cout << "[CommandHandler] Unexpected number of integers(" << numbOfIntInCommand  << ") in "<< commandToString(cmdType) << " command.\n";
	      sendError(command);
			}
			break;
		}
		case Command::SET_HEIGHT:
		{
			if (numbOfIntInCommand == 1)
			{
				m_picturePainter.setHeight(res[0]);
        sendAckStatus();
			}
			else
			{
				std::cout << "[CommandHandler] Unexpected number of integers(" << numbOfIntInCommand  << ") in "<< commandToString(cmdType) << " command.\n";
	      sendError(command);
			}
			break;
		}
		case Command::DRAW_RECTANGLE:
		{
			if (numbOfIntInCommand == 4)
			{
				m_picturePainter.drawRectangle(Point(res[0], res[1]), res[2], res[3]);
        sendAckStatus();
			}
			else
			{
				std::cout << "[CommandHandler] Unexpected number of integers(" << numbOfIntInCommand  << ") in "<< commandToString(cmdType) << " command.\n";
	      sendError(command);
			}
			break;
		}
		case Command::DRAW_TRIANGLE:
		{
			if (numbOfIntInCommand == 6)
			{
				m_picturePainter.drawTriangle(Point(res[0], res[1]), Point(res[2], res[3]), Point(res[4], res[5]));
        sendAckStatus();
			}
			else
			{
				std::cout << "[CommandHandler] Unexpected number of integers(" << numbOfIntInCommand  << ") in "<< commandToString(cmdType) << " command.\n";
	      sendError(command);
			}
			break;
		}
		case Command::RENDER:
		{
			m_picturePainter.saveFile(extractFilename(command));
      sendAckStatus();
			break;
		}
		case Command::NOT_FOUND:
		default:
		{
			std::cout << "[CommandHandler] ERROR \"" << command << "\" not recognized\n";
			sendError(command);
		}
	}
}

Command CommandHandler::parseCommand(const std::string command)
{
  boost::cmatch foundedElem;
	for (unsigned int idx = 0; idx < COMANDS_SIZE; ++idx)
	{
		if (boost::regex_match(command.c_str(), foundedElem, AVAILABLE_COMMANDS[idx]))
		  return static_cast<Command>(idx);
	}
	return Command::NOT_FOUND;
}

std::vector<int> CommandHandler::extractInteger(std::string command)
{
	std::replace(command.begin(), command.end(), ',' , ' ');
	std::stringstream command_stream;
	std::string word;
	int founded_number;
	std::vector<int> result{};

	command_stream << command;
	while (not command_stream.eof())
	{
	  command_stream >> word;
	  if (std::stringstream(word) >> founded_number)
	  {
	    result.push_back(founded_number);
	  }
	  word = "";
	}
    return result;
}

std::string CommandHandler::extractFilename(std::string command)
{
  std::stringstream command_stream;
  std::string word;

  command_stream << command;
  while (not command_stream.eof())
  {
    command_stream >> word;
    if (word != "RENDER")
    {
      return word;
    }
    word = "";
  }
  return PICTURE_DEFAULT_FILENAME;
}

std::string CommandHandler::commandToString(Command cmd)
{
	switch(cmd)
	{
		case Command::SET_WIDTH:
		{
			return "SET_WIDTH";
		}
		case Command::SET_HEIGHT:
		{
			return "SET_HEIGHT";
		}
		case Command::DRAW_RECTANGLE:
		{
			return "DRAW_RECTANGLE";
		}
		case Command::DRAW_TRIANGLE:
		{
			return "DRAW_TRIANGLE";
		}
		case Command::RENDER:
		{
			return "RENDER";
		}
		case Command::NOT_FOUND:
		{
			return "NOT_FOUND";
		}
	}
	return "NOT_FOUND";
}

void CommandHandler::sendError(std::string errorLog)
{
  try
  {
    std::cout << "[CommandHandler] Sending error \"" << errorLog << "\"\n";;
    m_sendingErrorMsgQueue.send(errorLog.data(), errorLog.size(), 0);
  }
  catch (interprocess_exception& e)
  {
      std::cout << e.what( ) << std::endl;
  }
}

void CommandHandler::sendAckStatus()
{
  try
  {
    std::cout << "[CommandHandler] Sending ACK status\n";
    m_sendingErrorMsgQueue.send(NO_ERROR.data(), NO_ERROR.size(), 0);
  }
  catch (interprocess_exception& e)
  {
      std::cout << e.what( ) << std::endl;
  }
}
