This app realizes following requirements:
1. Commands can be provided in two ways in Command Executor process:
  - from prompt: only type your command in console and ENTER it
  - from file: run application with filename as an argument e.g. ./Application commandList.txt 
2. Commands are sent to another proceess (Command Handler) by message_queue (boost IPC mechanism)
3. Command are interpreted by Command Handler:
  - if command is expected* it will be executed and some image processing will be applied.
  - if not Command Handler send error with command name to Command Executor
4. Command Executor checking if error occur in interpreting commands if yes it will be logged to log.txt file.

*Supported commands:
SET_WIDTH W
SET_HEIGHT H
DRAW_RECTANGLE X,Y,W,H 
RENDER NAME

<b>Used technology</b>
boost 1.58.0
OpenCV
-std=c++14

<b>Need to specify following libs:</b>
opencv_core
opencv_imgcodecs
opencv_highgui
opencv_imgproc
rt
pthread
boost_regex

<b>Limitation:</b>
maximum number of messages between processes is 1000, it's specify in MessageCommunication.h -> MAX_MSG_IN_QUEUE
maximum size of message is 100, it's specify in MessageCommunication.h -> MAX_MSG_SIZE
picture saving mode is jpeg, it's specify in PicturePainter.cpp -> JPEG_EXTENSION compressionPparams.push_back(cv::IMWRITE_JPEG_QUALITY);
errors are reported to log.txt file, specify in ErrorLogger.h -> errorFilename
