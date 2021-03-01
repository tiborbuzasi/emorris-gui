/**
 * Input Type - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef INPUT_TYPE_H
#define INPUT_TYPE_H

enum InputType
{
    INPUT_KEYBOARD,
    INPUT_MOUSE,
    INPUT_CONTROLLER
};

/** Number of input types */
const unsigned char NUM_OF_INPUT_TYPES = 3;

/** Name of the input types */
const std::array<std::string, NUM_OF_INPUT_TYPES> INPUT_TYPE_NAMES =
{
    "keyboard",
    "mouse",
    "controller"
};

#endif // INPUT_TYPE_H
