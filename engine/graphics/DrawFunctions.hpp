/**
 * Draw Functions - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef DRAW_FUNCTIONS_H
#define DRAW_FUNCTIONS_H

#include "../InterfaceManager.hpp"
#include "AlignmentType.hpp"
#include "Colors.hpp"
#include "GraphicsHandler.hpp"

class DrawFunctions
{
private:
    /** Graphics handler */
    static GraphicsHandler* gh;

public:
    /**
     * Initialize display manager
     *
     * @param[in]   graphicsHandler    Pointer to the graphics handler
     */
    static void Initialize(GraphicsHandler* graphicsHandler);

    /**
     * Lock/unlock sprite
     *
     * @param[in]   textureName         Name of the texture
     * @param[in]   lock                New lock state (true is lock, false is unlock)
     */
    static void Lock(std::string textureName, bool lock);

    /**
     * Draw sprite
     *
     * @param[in]   textureName         Name of the texture
     * @param[in]   resourceName        Name of the image resource
     * @param[in]   positionX           X coordinate of the position to draw to
     * @param[in]   positionY           Y coordinate of the position to draw to
     * @param[in]   zIndex              z-index of the sprite (default is on top)
     * @param[in]   horizontalAlignment Horizontal alignment of the image to the position (default is none)
     * @param[in]   verticalAlignment   Vertical alignment of the image to the position (default is none)
     */
    static void Sprite(std::string textureName,
                       std::string resourceName,
                       unsigned short int positionX,
                       unsigned short int positionY,
                       unsigned char zIndex = ZINDEX_LAST,
                       AlignmentType horizontalAlignment = ALIGN_NONE,
                       AlignmentType verticalAlignment = ALIGN_NONE);

    /**
     * Draw text
     *
     * @param[in]   text                Text to display
     * @param[in]   fontName            Name of the font resource
     * @param[in]   color               Color of the text
     * @param[in]   positionX           X coordinate of the position to draw to
     * @param[in]   positionY           Y coordinate of the position to draw to
     * @param[in]   zIndex              z-index of the sprite (default is on top)
     * @param[in]   horizontalAlignment Horizontal alignment of the image to the position (default is none)
     * @param[in]   verticalAlignment   Vertical alignment of the image to the position (default is none)
     */
    static void Text(std::string text,
                     std::string fontName,
                     SDL_Color color,
                     unsigned short int positionX,
                     unsigned short int positionY,
                     unsigned char zIndex = ZINDEX_LAST,
                     AlignmentType horizontalAlignment = ALIGN_NONE,
                     AlignmentType verticalAlignment = ALIGN_NONE);
};

typedef DrawFunctions draw;

#endif // DRAW_FUNCTIONS_H
