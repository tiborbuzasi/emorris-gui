/**
 * Menu controller - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "../engine/objects/ObjectIncludes.hpp"

class MenuController : public Object
{
private:
    /** Menu identifier */
    unsigned char menuId = 0;

    /** Game mode */
    unsigned char gameMode = 0;

public:
    /**
     * Construct object
     *
     * @param[in]   groupName           The name of the texture group
     * @param[in]   objectName          The name of the object
     */
    MenuController(std::string groupName, std::string objectName);

    /**
     * Create object
     */
    void Create();

    /**
     * Destroy object
     */
    void Destroy();

    /**
     * Update object
     */
    void Update();

    /**
     * Draw object
     */
    void Draw();

    /**
     * Handle input for object
     */
    void Input(SDL_Event event);

    /**
     * Execute selected menu item
     */
    void Execute();

};

#endif // MENU_CONTROLLER_H
