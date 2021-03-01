/**
 * Utility Functions
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "UtilityFunctions.hpp"

#include <fstream>

#include "../AppInfo.hpp"

void Log(std::string objectName, std::string log, bool show, bool write)
{
	// Output log to console
	if (show)
	{
		std::cout << objectName << ": " << log << std::endl;
	}
	// Write log into log file
	if (write)
	{
		// Create log filename
		std::string fileName = APP_NAME;
		fileName += LOG_FILE_EXT;

		// Open log file
		std::ofstream logFile(fileName, std::ios::out | std::ios::app);
		if (!logFile.is_open())
		{
			std::cout << "Log: " + fileName + ": opening log file to write failed."<< std::endl;
			return;
		}

		// Append log to log file
		logFile << objectName << ": " << log << std::endl;
		logFile.close();
	}
}
