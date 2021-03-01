/**
 * Position - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef POSITION_H
#define POSITION_H

struct Position
{
    /** Z-index of the texture (0-255: from first to last render) */
    unsigned char zIndex;

    /** X coordinate of the rendering position */
    unsigned short int x;

    /** Y coordinate of the rendering position */
    unsigned short int y;
};

/** First z-index to render */
const unsigned char ZINDEX_FIRST = 0;

/** Last z-index to render */
const unsigned char ZINDEX_LAST = 255;

#endif // POSITION_H
