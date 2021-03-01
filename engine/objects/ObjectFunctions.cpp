/**
 * Object Functions
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "../UtilityFunctions.hpp"
#include "ObjectFunctions.hpp"

ObjectManager* ObjectFunctions::om = nullptr;

void ObjectFunctions::Initialize(ObjectManager* objectManager)
{
    ObjectFunctions::om = objectManager;
    if (om == nullptr)
    {
        Log("Object functions", "initialization failed: ObjectManager not found.", true, true);
        exit(1);
    }
}

void ObjectFunctions::Create(Object* object)
{
    om->CreateObject(object);
}

void ObjectFunctions::Destroy(std::string objectName)
{
    om->DestroyObject(objectName);
}

Object* ObjectFunctions::Get(std::string objectName)
{
    return om->GetObject(objectName);
}
