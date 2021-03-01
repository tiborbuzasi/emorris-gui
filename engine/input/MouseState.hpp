/**
 * Mouse State - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef MOUSE_STATE_H
#define MOUSE_STATE_H

#include <array>

struct MouseState
{
    /** X coordinate of the mouse position */
    unsigned short int x = 0;
    /** Y coordinate of the mouse position */
    unsigned short int y = 0;
    /** Mouse position changed */
    bool positionChanged = false;
    /** Mouse button is pressed */
    std::array<bool, 5> buttonPressed = { false };
    /** Mouse button is held */
    std::array<bool, 5> buttonHeld = { false };
    /** Mouse button is released */
    std::array<bool, 5> buttonReleased = { false };
};

/** Number of mouse buttons */
const unsigned char NUM_OF_MOUSE_BUTTONS = 5;

/** Index of the last mouse state */
const unsigned char STATE_LAST = 0;

/** Index of the current mouse state */
const unsigned char STATE_CURRENT = 1;

/** Index of the left mouse button */
const unsigned char BUTTON_LEFT = 0;

/** Index of the middle mouse button */
const unsigned char BUTTON_MIDDLE = 1;

/** Index of the right mouse button */
const unsigned char BUTTON_RIGHT = 2;

#endif // MOUSE_STATE_H
