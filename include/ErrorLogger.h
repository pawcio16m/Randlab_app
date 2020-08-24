/*
 * ErrorLogger.h
 *
 *  Created on: 21 sie 2020
 *      Author: pmusial
 */
#pragma once

#include <string>

class ErrorLogger {
public:
	ErrorLogger();
	virtual ~ErrorLogger() = default;
	void logError(std::string);

private:
	std::string errorFilename = "log.txt";
};
