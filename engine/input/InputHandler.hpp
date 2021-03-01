/**
 * Input Handler for Interface Manager - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "../ResourceManager.hpp"
#include "InputType.hpp"
#include "MouseState.hpp"
#include "../objects/Object.hpp"

class InputHandler
{
private:
    /** Object name */
    const std::string objectName = "InputHandler";

    /** Resource manager */
    ResourceManager* rm = nullptr;

    /** Vector of pointers to objects to handle input */
    std::array<std::vector<Object*>, 3> objects;

    /** Temporary vector of pointers to objects (for adding objects) */
    std::array<std::vector<Object*>, 3> tempObjects;

    /** Game controllers */
    std::vector<SDL_GameController*> controllers;

    /** Mouse states (last and current) */
    std::array<MouseState, 2> mouseStates;

    /**
     * Get object
     *
     * @param[in]   objectName          Name of the object
     *
     * @return      Iterator to the object
     */
    std::vector<Object*>::iterator GetObject(InputType inputType, std::string objectName);

    /**
     * Check input type is valid
     *
     * @param[in]   inputType           Input type
     *
     * @return      The input type is valid
     */
    bool CheckInputType(InputType inputType);

    /**
     * Update mouse state (based on input events)
     *
     * @param[in]   inputEvent          Input event
     */
    void UpdateMouseState(SDL_Event* inputEvent);

public:
    /**
     * Initialize input handler
     *
     * @param[in]   resourceManager     Pointer to the resource manager
     */
    InputHandler(ResourceManager* resourceManager);

    /**
     * Handle input for objects
     */
    void Input();

    /**
     * Add object to input handling
     *
     * @param[in]   inputType           Input type
     * @param[in]   objectName          The object to handle the input for
     */
    bool AddObject(InputType inputType, Object* object);

    /**
     * Remove object from input handling
     *
     * @param[in]   inputType           Input type
     * @param[in]   objectName          Name of the object
     */
    void RemoveObject(InputType inputType, std::string objectName);

    /**
     * Get mouse state
     *
     * @return      Current mouse state
     */
    MouseState GetMouseState();
};

#endif // INPUT_HANDLER_H
