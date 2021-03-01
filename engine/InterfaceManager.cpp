/**
 * Interface Manager
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "InterfaceManager.hpp"

#include "../AppInfo.hpp"
#include "UtilityFunctions.hpp"

bool InterfaceManager::Initialize(ResourceManager* resourceManager)
{
    rm = resourceManager;
    if (rm == nullptr)
    {
        Log(objectName, "initialization failed: ResourceManager not found.", true, true);
        exit(1);
    }

    // Initialize SDL, SDL_image ans SDL_ttf systems
    if (SDL_Init(SDL_INIT_VIDEO | /*SDL_INIT_AUDIO |*/ SDL_INIT_GAMECONTROLLER) != 0)
    {
        Log(objectName, SDL_GetError(), true, true);
        exit(1);
    }
    if (!IMG_Init(IMG_INIT_PNG))
    {
        Log(objectName, IMG_GetError(), true, true);
        exit(1);
    }
    if (TTF_Init() != 0)
    {
        Log(objectName, TTF_GetError(), true, true);
        exit(1);
    }

    // Create the window
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    if (rm->GetAttribute(RESTYPE_SETTINGS, "Settings", "Video", "fullScreen") == "1")
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    int resolutionX = std::atoi((rm->GetAttribute(RESTYPE_SETTINGS, "Settings", "Video", "resolutionX")).c_str());
    int resolutionY = std::atoi((rm->GetAttribute(RESTYPE_SETTINGS, "Settings", "Video", "resolutionY")).c_str());

    window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, resolutionX, resolutionY, windowFlags);
    if (window == nullptr)
    {
        Log(objectName, SDL_GetError(), true, true);
        exit(1);
    }

    // Create the graphics handler
    graphicsHandler = new GraphicsHandler(rm, window);
    if (graphicsHandler == nullptr)
    {
        Log(objectName, "initialization failed: GraphicsHandler not found.", true, true);
    }

    // Create the input handler
    inputHandler = new InputHandler(rm);
    if (inputHandler == nullptr)
    {
        Log(objectName, "initialization failed: InputHandler not found.", true, true);
    }

    atexit(TTF_Quit);
    atexit(IMG_Quit);
    atexit(SDL_Quit);

    return true;
}

ResourceManager* InterfaceManager::GetResourceManager()
{
    return rm;
}

SDL_Window* InterfaceManager::GetWindow()
{
    return window;
}

GraphicsHandler* InterfaceManager::GetGraphicsHandler()
{
    return graphicsHandler;
}

InputHandler* InterfaceManager::GetInputHandler()
{
    return inputHandler;
}

bool InterfaceManager::CheckQuit()
{
    SDL_Event inputEvent;
    SDL_PumpEvents();
    if (SDL_PeepEvents(&inputEvent, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT))
    {
        Log(objectName, "closing application.", true, true);
        return true;
    }

    return false;
}
