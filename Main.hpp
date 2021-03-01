/**
 * Application Main - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef MAIN_H
#define MAIN_H

#include "engine/InterfaceManager.hpp"
#include "engine/ObjectManager.hpp"
#include "engine/ResourceManager.hpp"

/** Resource manager */
ResourceManager* rm = nullptr;

/** Interface manager */
InterfaceManager* im = nullptr;

/** Interface manager */
ObjectManager* om = nullptr;

#endif // MAIN_H
