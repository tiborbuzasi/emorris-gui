/**
 * Texture - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_render.h"

#include "Position.hpp"

struct Texture
{
    /** Resource name */
    std::string textureName;

    /** Pointer to the texture (in ResourceManager) */
    SDL_Texture* texture;

    /** The texture has changed */
    bool changed;

    /** The texture is hidden */
    bool hidden;

    /** Z-index and position of the texture */
    Position position;

    /** The texture is locked (to prevent it from being automatically removed) */
    bool locked;

    /** The texture can be automatically removed */
    bool autoRemove;
};

#endif // #define TEXTURE_H
