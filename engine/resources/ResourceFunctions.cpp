/**
 * Resource Functions
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "ResourceFunctions.hpp"

#include "../UtilityFunctions.hpp"

ResourceManager* ResourceFunctions::rm = nullptr;

void ResourceFunctions::Initialize(ResourceManager* resourceManager)
{
    rm = resourceManager;
    if (rm == nullptr)
    {
        Log("Resource functions", "initialization failed: ResourceManager not found.", true, true);
        exit(1);
    }
}

void ResourceFunctions::Load(std::string resourceName, std::string resourcePath)
{
    rm->LoadResource(resourceName, resourcePath);
}

void ResourceFunctions::Unload(ResourceType resourceType, std::string resourceName)
{
    rm->UnloadResource(resourceType, resourceName);
}

std::string ResourceFunctions::GetAttribute(ResourceType resourceType,
        std::string resourceName,
        std::string attributeGroup,
        std::string attributeName)
{
    return rm->GetAttribute(resourceType, resourceName, attributeGroup, attributeName);
}

bool ResourceFunctions::AddAttribute(ResourceType resourceType,
                                     std::string resourceName,
                                     std::string attributeGroup,
                                     std::string attributeName,
                                     std::string attributeValue)
{
    return rm->AddAttribute(resourceType, resourceName, attributeGroup, attributeName, attributeValue);
}

bool ResourceFunctions::ChangeAttribute(ResourceType resourceType,
                                        std::string resourceName,
                                        std::string attributeGroup,
                                        std::string attributeName,
                                        std::string newValue)
{
    return rm->ChangeAttribute(resourceType, resourceName, attributeGroup, attributeName, newValue);
}
