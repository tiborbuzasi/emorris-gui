/**
 * Input Functions - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef INPUT_FUNCTIONS_H
#define INPUT_FUNCTIONS_H

#include "InputHandler.hpp"

class InputFunctions
{
private:
    /** Input handler */
    static InputHandler* ih;

public:
    /**
     * Initialize input manager
     *
     * @param[in]   inputHandler    Pointer to the input handler
     */
    static void Initialize(InputHandler* inputHandler);

    /**
     * Add object to input handling
     *
     * @param[in]   inputType           Input type
     * @param[in]   objectName          The object to handle the input for
     */
    static void Add(InputType inputType, Object* object);

    /**
     * Remove object from input handling
     *
     * @param[in]   inputType           Input type
     * @param[in]   objectName          Name of the object
     */
    static void Remove(InputType inputType, std::string objectName);

    /**
     * Get mouse state
     *
     * @return      The current mouse state
     */
    static MouseState GetMouseState();
};

typedef InputFunctions input;

#endif // INPUT_FUNCTIONS_H
