/**
 * Object (abstract class) - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "../ResourceManager.hpp"
#include "../graphics/GraphicsHandler.hpp"
#include "../graphics/Position.hpp"

class Object
{
private:
    /** Object name */
    std::string objectName;

    /** Group name */
    std::string groupName;

    /** Object is disabled (Update method is not executed) */
    bool disabled = false;

    /** Texture */
    Texture texture;

public:
    /**
     * Create and initialize object
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   objectName          Name of the object
     * @param[in]   x                   X coordinate of the position
     * @param[in]   y                   Y coordinate of the position
     */
    Object(std::string groupName, std::string objectName, unsigned short int x = 0, unsigned short y = 0);

    /**
     * Create object
     */
    virtual void Create() = 0;

    /**
     * Destroy object
     */
    virtual void Destroy() = 0;
    virtual ~Object();

    /**
     * Update object
     */
    virtual void Update() = 0;

    /**
     * Draw object
     */
    virtual void Draw() = 0;

    /**
     * Handle input for object
     */
    virtual void Input(SDL_Event event) = 0;

    /**
     * Get object name
     *
     * @return      The object's name
     */
    std::string GetName();

    /**
     * Get group name
     *
     * @return      The name of the object's group
     */
    std::string GetGroupName();

    /**
     * Get disabled state
     *
     * @return      The object's disabled state
     */
    bool GetDisabled();

    /**
     * Set disabled state
     *
     * @param[in]   disabled            New state value
     */
    void SetDisabled(bool disabled);

    /**
     * Get hidden state
     *
     * @return      The object's hidden state
     */
    bool GetHidden();

    /**
     * Set hidden state
     *
     * @param[in]   hidden              New state value
     */
    void SetHidden(bool hidden);

    /**
     * Get position
     *
     * @return      The objects' z-index and position
     */
    Position GetPosition();

    /**
     * Set position
     *
     * @param[in]   x                   X coordinate of the position
     * @param[in]   y                   Y coordinate of the position
     */
    void SetPosition(unsigned short int x, unsigned short int y);

    /**
     * Set position
     *
     * @param[in]   position            Position of the texture
     */
    void SetPosition(Position position);

    /**
     * Get texture
     *
     * @return      Pointer to the texture
     */
    Texture* GetTexture();

    /**
     * Set texture resource and z-index
     *
     * @param[in]   resourceName        Name of the sprite
     * @param[in]   zIndex              z-index of the sprite
     */
    void SetTexture(std::string resourceName, unsigned char zIndex = ZINDEX_LAST);
};

#endif // OBJECT_H
