/**
 * Input Functions
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "InputFunctions.hpp"

#include "../UtilityFunctions.hpp"

InputHandler* InputFunctions::ih = nullptr;

void InputFunctions::Initialize(InputHandler* inputHandler)
{
    ih = inputHandler;
    if (ih == nullptr)
    {
        Log("Input functions", "initialization failed: InputHandler not found.", true, true);
        exit(1);
    }
}

void InputFunctions::Add(InputType inputType, Object* object)
{
    ih->AddObject(inputType, object);
}

void InputFunctions::Remove(InputType inputType, std::string objectName)
{
    ih->RemoveObject(inputType, objectName);
}

MouseState InputFunctions::GetMouseState()
{
    return ih->GetMouseState();
}
