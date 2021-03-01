/**
 * Object Manager
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "ObjectManager.hpp"

#include "UtilityFunctions.hpp"
#include "objects/Object.hpp"

ObjectManager::ObjectManager(InterfaceManager* interfaceManager)
{
    im = interfaceManager;
    if (im == nullptr)
    {
        Log(objectName, "initialization failed: InterfaceManager not found.", true, true);
        exit(1);
    }
}

void ObjectManager::CreateObject(Object* object)
{
    if (object == nullptr)
    {
        Log(objectName, "creating object failed.");
        return;
    }
    objects.push_back(object);

    // Create texture group
    im->GetGraphicsHandler()->CreateGroup(object->GetGroupName(), object->GetTexture()->position.zIndex);

    // Run object specific creation code
    object->Create();

    // Add texture to graphics handler
    if (object->GetTexture()->textureName != "")
    {
        Texture* texture = object->GetTexture();
        im->GetGraphicsHandler()->DrawSprite(object->GetGroupName(), object->GetName(), texture->textureName,
                                             texture->position.x, texture->position.y, texture->position.zIndex,
                                             ALIGN_NONE, ALIGN_NONE);
        texture->changed = false;
    }
}

void ObjectManager::DestroyObject(std::string objectName)
{
    for (std::vector<Object*>::iterator oi = objects.begin(); oi != objects.end();
            ++oi)
    {
        if ((*oi)->GetName() != objectName)
        {
            continue;
        }

        // Destroy texture if set
        if ((*oi)->GetTexture()->textureName != "")
        {
            im->GetGraphicsHandler()->RemoveTexture((*oi)->GetGroupName(), objectName);
        }

        // Destroy object
        (*oi)->Destroy();
        delete (*oi);
        oi = objects.erase(oi);

        return;
    }
}

Object* ObjectManager::GetObject(std::string objectName)
{
    for (std::vector<Object*>::iterator oi = objects.begin(); oi != objects.end();
            ++oi)
    {
        if ((*oi)->GetName() == objectName)
        {
            return *oi;
        }
    }

    return nullptr;
}

void ObjectManager::Update()
{
    for (unsigned long index = 0; index < objects.size();
            ++index)
    {
        // Run object specific update code
        if (objects[index] != nullptr && !objects[index]->GetDisabled())
        {
            objects[index]->Update();
        }
    }
}

void ObjectManager::Draw()
{

    for (std::vector<Object*>::iterator oi = objects.begin(); oi != objects.end();
            ++oi)
    {
        Object* object = (*oi);

        // Run object specific draw code
        object->Draw();

        // Check if object texture has changed
        if (!object->GetTexture()->changed)
        {
            continue;
        }
        object->GetTexture()->changed = false;

        // Check if object texture is hidden
        Texture* texture = im->GetGraphicsHandler()->GetTexture(object->GetGroupName(), object->GetName());
        if (object->GetHidden() || object->GetTexture()->textureName != texture->textureName
                || object->GetTexture()->position.zIndex != texture->position.zIndex)
        {
            im->GetGraphicsHandler()->RemoveTexture(object->GetGroupName(), object->GetName());
        }

        // Check if new object texture exists
        if (object->GetTexture()->textureName == "")
        {
            continue;
        }

        // Add texture
        texture = object->GetTexture();
        im->GetGraphicsHandler()->DrawSprite(object->GetGroupName(), object->GetName(), texture->textureName,
                                             texture->position.x, texture->position.y, texture->position.zIndex,
                                             ALIGN_NONE, ALIGN_NONE);

        Log(objectName, object->GetName() + ": changed texture to " + texture->textureName + ".", true, true);
    }
}
