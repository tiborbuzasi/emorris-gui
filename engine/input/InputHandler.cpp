/**
 * Input Handler for Interface Manager
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "InputHandler.hpp"

#include "../UtilityFunctions.hpp"

InputHandler::InputHandler(ResourceManager* resourceManager)
{
    // Set pointer to resource manager
    rm = resourceManager;

    if (rm == nullptr)
    {
        Log(objectName, "initialization failed: ResourceManager not found.", true, true);
        exit(1);
    }

    if (SDL_GameControllerAddMapping("030000000b0400003365000000010000,A SPEED-LINK Competition Pro,platform:Linux,a:b0,b:b1,x:b2,y:b3,dpup:-a1,dpdown:+a1,dpleft:-a0,dpright:+a0") < 0)
    {
        Log(objectName, "controller: creating mapping failed.", true, true);
    }
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (!SDL_IsGameController(i))
        {
            continue;
        }

        SDL_GameController* controller = SDL_GameControllerOpen(i);
        if (!controller)
        {
            Log(objectName, "controller: " + (std::string) SDL_GetError(), true, true);
            continue;
        }

        controllers.push_back(controller);
        Log(objectName, "controller: " + (std::string) SDL_GameControllerName(controller) + " is connected.", true, true);
    }
}

void InputHandler::Input()
{
    SDL_PumpEvents();

    // FIXME: define mouse state
//     #ifdef INPUT_MOUSE_STATE
    // Update mouse state
    SDL_Event* inputEvents = new SDL_Event[16];
    for (unsigned char i = 0; i < SDL_PeepEvents(inputEvents, 16, SDL_PEEKEVENT, SDL_MOUSEMOTION, SDL_MOUSEWHEEL); ++i)
    {
        UpdateMouseState(&inputEvents[0]);
    }
    UpdateMouseState(nullptr);
//     #endif // INPUT_MOUSE_STATE

    for (unsigned char inputType = 0; inputType < NUM_OF_INPUT_TYPES; ++inputType)
    {
        SDL_EventType from, to;
        switch (inputType)
        {
        case INPUT_KEYBOARD:
            from = SDL_KEYDOWN;
            to = SDL_KEYUP;
            break;
        case INPUT_MOUSE:
            from = SDL_MOUSEMOTION;
            to = SDL_MOUSEWHEEL;
            break;
        case INPUT_CONTROLLER:
            from = SDL_CONTROLLERAXISMOTION;
            to = SDL_CONTROLLERDEVICEREMAPPED;
            break;
        }

        SDL_Event inputEvent;
        while (SDL_PeepEvents(&inputEvent, 1, SDL_GETEVENT, from, to))
        {
            std::vector<Object*>::iterator oi;

            for (oi = objects[inputType].begin(); oi != objects[inputType].end(); ++oi)
            {
                (*oi)->Input(inputEvent);
            }
        }

        // Adding objects from temporary container
        // TODO: check if object already exists
        std::vector<Object*>::iterator toi;
        for (toi = tempObjects[inputType].begin(); toi != tempObjects[inputType].end(); ++toi)
        {
            objects[inputType].emplace_back((*toi));
        }
        tempObjects[inputType].clear();
    }
}

bool InputHandler::AddObject(InputType inputType, Object* object)
{
    // Check if input type is valid
    if (!CheckInputType(inputType))
    {
        Log(objectName, "add object failed: invalid input type.", true, true);
        return false;
    }

    // Check if object exists
    std::vector<Object*>::iterator oi = GetObject(inputType, object->GetName());
    if (oi != objects[inputType].end())
    {
        Log(objectName, INPUT_TYPE_NAMES[inputType] + ": add object failed: " + object->GetName() + " already exists.", true,
            true);
        return false;
    }

    // Add object
    tempObjects[inputType].emplace_back(object);
    Log(objectName, INPUT_TYPE_NAMES[inputType] + ": " + object->GetName() + " added to input handler.", true, true);

    return true;
}

void InputHandler::RemoveObject(InputType inputType, std::string objectName)
{
    // Check if input type is valid
    if (!CheckInputType(inputType))
    {
        Log(objectName, "remove object failed: invalid input type.", true, true);
        return;
    }

    // Check if object exists
    std::vector<Object*>::iterator oi = GetObject(inputType, objectName);
    if (oi == objects[inputType].end())
    {
        Log(objectName, INPUT_TYPE_NAMES[inputType] + ": remove object failed: " + objectName + " doesn't exist.",
            true, true);
        return;
    }

    objects[inputType].erase(oi);
    Log(objectName, INPUT_TYPE_NAMES[inputType] + ": " + objectName + " removed from input handler.", true, true);
}

MouseState InputHandler::GetMouseState()
{
    return mouseStates[STATE_CURRENT];
}

std::vector<Object*>::iterator InputHandler::GetObject(InputType inputType, std::string objectName)
{
    std::vector<Object*>::iterator oi;

    for (oi = objects[inputType].begin(); oi != objects[inputType].end(); ++oi)
    {
        if ((*oi)->GetName() == objectName)
        {
            break;
        }
    }

    return oi;
}

bool InputHandler::CheckInputType(InputType inputType)
{
    if (inputType < 0 || inputType > 2)
    {
        return false;
    }

    return true;
}

void InputHandler::UpdateMouseState(SDL_Event* inputEvent)
{
    // Update button states if no event occurred
    if (inputEvent == nullptr)
    {
        // Check changes of mouse button states
        for (unsigned char i = 0; i < NUM_OF_INPUT_TYPES; ++i)
        {
            mouseStates[STATE_CURRENT].buttonPressed[i] = !mouseStates[STATE_LAST].buttonHeld[i]
                    && mouseStates[STATE_CURRENT].buttonHeld[i];
            mouseStates[STATE_CURRENT].buttonReleased[i] = mouseStates[STATE_LAST].buttonHeld[i]
                    && !mouseStates[STATE_CURRENT].buttonHeld[i];
        }

        // Check change of mouse position state
        mouseStates[STATE_CURRENT].positionChanged = (mouseStates[STATE_CURRENT].x != mouseStates[STATE_LAST].x)
                || (mouseStates[STATE_CURRENT].y != mouseStates[STATE_LAST].y);

        // Set current state as last state
        mouseStates[STATE_LAST] = mouseStates[STATE_CURRENT];
        return;
    }

    // Handle mouse related events
    switch (inputEvent->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        mouseStates[STATE_CURRENT].buttonHeld[inputEvent->button.button - 1] = true;
        break;
    case SDL_MOUSEBUTTONUP:
        mouseStates[STATE_CURRENT].buttonHeld[inputEvent->button.button - 1] = false;
        break;
    case SDL_MOUSEMOTION:
        mouseStates[STATE_CURRENT].x = inputEvent->motion.x;
        mouseStates[STATE_CURRENT].y = inputEvent->motion.y;
        break;
    }
}
