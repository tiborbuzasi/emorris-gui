/**
 * Constants - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/** Background color */
const SDL_Color COLOR_BACKGROUND = { 64, 96, 64, 255 };

/** Canvas width */
const unsigned short int CANVAS_WIDTH = 1920;

/** Canvas height */
const unsigned short int CANVAS_HEIGHT = 1080;

/** Canvas center X coordinate */
const unsigned short int CENTER_X = CANVAS_WIDTH / 2;

/** Canvas center X coordinate */
const unsigned short int CENTER_Y = CANVAS_HEIGHT / 2;

/** Block size */
const unsigned short int BLOCK_SIZE = 52;

/** Mapping of piece positions in a game square */
const unsigned char SQUARE_MAP[3][3] = { {0, 7, 6}, {1, 0, 5}, {2, 3, 4}};

#endif // CONSTANTS_H
