/**
 * Utility Functions - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include <iostream>

/** Log file extension */
const std::string LOG_FILE_EXT = ".log";

/**
 * @brief Log
 *
 * Show log in console and/or write log into logfile.
 *
 * @param[in]   objectName  Name of the object
 * @param[in]   log         Log content
 * @param[in]   show        Show log in console (true by default)
 * @param[in]   write       Write log into logfile (false by default)
 */
void Log(std::string objectName, std::string log, bool show = true, bool write = false);

#endif // UTILITY_FUNCTIONS_H
