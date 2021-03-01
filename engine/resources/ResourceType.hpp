/**
 * Resource Type - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef RESOURCE_TYPE_H
#define RESOURCE_TYPE_H

#include <array>

enum ResourceType
{
    RESTYPE_SETTINGS = 1,
    RESTYPE_LANGUAGE,
    RESTYPE_MENU,
    RESTYPE_FONT,
    RESTYPE_IMAGE,
    RESTYPE_AUDIO,
    RESTYPE_WORLD,
    RESTYPE_LEVEL
};

/** Name of the resource types */
const std::array<std::string,8> RESTYPE_NAMES =
{
        "settings",
        "language",
        "menu",
        "font",
        "image",
        "audio",
        "world",
        "level"
};

#endif // RESOURCE_TYPE_H
