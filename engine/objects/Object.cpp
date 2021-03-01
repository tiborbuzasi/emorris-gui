/**
 * Object (abstract class)
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "Object.hpp"

#include "../UtilityFunctions.hpp"

Object::Object(std::string groupName, std::string objectName, unsigned short int x, unsigned short y)
{
    this->groupName = groupName;
    this->objectName = objectName;
    texture.textureName = "";
    texture.position = (Position) { ZINDEX_FIRST, x, y };
}

Object::~Object() {}

std::string Object::GetName()
{
    return objectName;
}

std::string Object::GetGroupName()
{
    return groupName;
}

bool Object::GetDisabled()
{
    return disabled;
}

void Object::SetDisabled(bool disabled)
{
    this->disabled = disabled;
}

bool Object::GetHidden()
{
    return texture.hidden;
}

void Object::SetHidden(bool hidden)
{
    texture.hidden = hidden;
    texture.changed = true;
}

Position Object::GetPosition()
{
    return texture.position;
}

void Object::SetPosition(unsigned short int x, unsigned short int y)
{
    SetPosition((Position)
    {
        texture.position.zIndex, x, y
    });
}

void Object::SetPosition(Position position)
{
    position.zIndex = texture.position.zIndex;
    texture.position = position;
    texture.changed = true;
}

Texture* Object::GetTexture()
{
    return &texture;
}

void Object::SetTexture(std::string resourceName, unsigned char zIndex)
{
    texture.textureName = resourceName;
    texture.changed = true;
}
