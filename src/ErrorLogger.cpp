/*
 * ErrorLogger.cpp
 *
 *  Created on: 21 sie 2020
 *      Author: pmusial
 */
#include <string>
#include <iostream>
#include <fstream>

#include "ErrorLogger.h"

ErrorLogger::ErrorLogger()
{
	std::ofstream errorFile;
	errorFile.open(errorFilename, std::ios::trunc);
	errorFile.close();
}

void ErrorLogger::logError(std::string error)
{
  std::cout << "[ErrorLogger] Logging error\"" << error << "\" to file " << errorFilename << std::endl;
	std::ofstream errorFile;
	errorFile.open(errorFilename, std::ios::in | std::ios::app);
	errorFile << error.c_str();
	errorFile << "\n";
	errorFile.close();
}

