/**
 * Interface Manager - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef INTERFACE_MANAGER_H
#define INTERFACE_MANAGER_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "ResourceManager.hpp"
#include "graphics/GraphicsHandler.hpp"
#include "input/InputHandler.hpp"

class InterfaceManager
{
private:
    /** Object name */
    const std::string objectName = "InterfaceManager";

    /** Resource manager */
    ResourceManager* rm = nullptr;

    /** Window */
	SDL_Window* window = nullptr;

	/** Graphics handler */
	GraphicsHandler* graphicsHandler = nullptr;

	/** Input handler */
	InputHandler* inputHandler = nullptr;

public:
	/**
     * Initializing framework systems
     *
     * @return Successful initialization
     */
	bool Initialize(ResourceManager* resourceManager);

	/**
	 * Get resource manager
	 *
	 * @return Resource manager
	 */
	ResourceManager* GetResourceManager();

	/**
	 * Get window
	 *
	 * @return Renderer
	 */
	SDL_Window* GetWindow();

	/**
	 * Get graphics handler
	 *
	 * @return Graphics handler
	 */
	GraphicsHandler* GetGraphicsHandler();

	/**
	 * Get input handler
	 *
	 * @return Input handler
	 */
	InputHandler* GetInputHandler();

	/**
	 * Check for quitting the application
	 */
    bool CheckQuit();
};

#endif // INTERFACE_MANAGER_H
