<b>This app realizes following requirements:</b>
  1. Commands can be provided in two ways in Command Executor process:<br>
    - from prompt: only type your command in console and ENTER it<br>
    - from file: run application with filename as an argument e.g. ./Application commandList.txt<br>
  2. Commands are sent to another proceess (Command Handler) by message_queue (boost IPC mechanism)<br>
  3. Command are interpreted by Command Handler:<br>
    - if command is expected* it will be executed and some image processing will be applied.<br>
    - if not Command Handler send error with command name to Command Executor<br>
  4. Command Executor checking if error occur in interpreting commands if yes it will be logged to log.txt file.<br>
  5. You can type exit in command line to terminate application<br>

*Supported commands:<br>
SET_WIDTH W<br>
SET_HEIGHT H<br>
DRAW_RECTANGLE X,Y,W,H<br> 
DRAW_TRIANGLE X1,Y1,X2,Y2,X3,Y3<br>
RENDER NAME<br>

<b>Used technology</b><br>
boost 1.58.0<br>
OpenCV<br>
-std=c++14<br>

<b>Need to specify following libs:</b><br>
opencv_core<br>
opencv_imgcodecs<br>
opencv_highgui<br>
opencv_imgproc<br>
rt<br>
pthread<br>
boost_regex<br>

They should be placed in lib folder. Moreover it may required adding libs to /usr/lib folder.<br>

<b>Limitation:</b><br>
maximum number of messages between processes is 1000, it's specify in MessageCommunication.h -> MAX_MSG_IN_QUEUE<br>
maximum size of message is 100, it's specify in MessageCommunication.h -> MAX_MSG_SIZE<br>
picture saving mode is jpeg, it's specify in PicturePainter.cpp -> JPEG_EXTENSION compressionParams.push_back(cv::IMWRITE_JPEG_QUALITY);<br>
errors are reported to log.txt file, specify in ErrorLogger.h -> errorFilename<br>

<b>Examples of usage and output from execution can be found in demo folder</b><br>
