/**
 * Application Main
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "Main.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "engine/graphics/GraphicsHandler.hpp"
#include "engine/graphics/DrawFunctions.hpp"
#include "engine/input/InputFunctions.hpp"
#include "engine/objects/ObjectFunctions.hpp"
#include "engine/resources/ResourceFunctions.hpp"
#include "engine/UtilityFunctions.hpp"
#include "AppInfo.hpp"

#include "objects/MenuController.hpp"

int main(int argc, char **argv)
{
    // Display application name and version
    std::cout << APP_NAME << " - Version " << APP_VERSION << std::endl << std::endl;

    // Initalize the resource manager, interface manager and object manager
    im = new InterfaceManager();
    rm = new ResourceManager();
    om = new ObjectManager(im);

    // Initialize SDL system and create window
    if (!rm->LoadResource("Settings"))
        exit(1);
    im->Initialize(rm);

    // Initialize the drawing, input, object and resource functions
    draw::Initialize(im->GetGraphicsHandler());
    input::Initialize(im->GetInputHandler());
    obj::Initialize(om);
    res::Initialize(rm);

    std::cout<<std::endl;

    // Create objects
    om->CreateObject(new MenuController("controllers", "MenuController"));

    // Wait for input
    std::cout << "Waiting for user interaction..." << std::endl;

    // Loop
    while (!im->CheckQuit())
    {
        im->GetInputHandler()->Input();
        om->Update();
        om->Draw();
        im->GetGraphicsHandler()->Render();
    }

    delete om;
    delete im;
    delete rm;

    return 0;
}
