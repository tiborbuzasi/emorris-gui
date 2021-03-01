/**
 * Texture Group - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef TEXTURE_GROUP_H
#define TEXTURE_GROUP_H

#include "Texture.hpp"

struct TextureGroup
{
    /** Texture group name */
    std::string groupName;

    /** The texture has changed */
    bool changed;

    /** Z-index and position of the texture */
    unsigned char zIndex;

    /** The list of textures */
    std::vector<Texture> textures;
};

#endif // TEXTURE_GROUP_H
