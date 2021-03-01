/**
 * Resource Manager
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "ResourceManager.hpp"

#include <unordered_map>

#include "UtilityFunctions.hpp"
#include "resources/XMLHandler.hpp"

bool ResourceManager::LoadResource(std::string resourceName, std::string resourcePath, bool reload)
{
    XMLHandler* xmlHandler = new XMLHandler();

    // Load XML file
    if (!xmlHandler->LoadXML(resourcePath, resourceName))
    {
        Log(objectName, "loading resource " + resourceName + " failed.", true, true);
        return false;
    }

    // Load all resources from XML file
    bool success = true;
    do
    {
        // Get resource name and type
        if (!xmlHandler->LoadResourceNameAndType())
        {
            success = false;
            continue;
        }
        ResourceDataType* data = xmlHandler->GetResourceData();

        // Check if resource is already loaded
        if (GetResourceData(data->type, data->name) && !reload)
        {
            Log(objectName, resourceName + ": resource data is already loaded.", true, true);
            continue;
        }

        // Get resource data
        xmlHandler->LoadResourceData();
        data = xmlHandler->GetResourceData();
        resourceDatas.push_back(*data);

        // Load resource file
        if (!LoadResourceFile(data->type, data->name))
        {
            success = false;
            continue;
        };
    }
    while (xmlHandler->GetNextResource());

    delete xmlHandler;

    return success;
}

void ResourceManager::UnloadResource(ResourceType resourceType, std::string resourceName)
{
    // TODO: implement unloading resources

    Log(objectName, "NOT IMPLEMENTED");
    return;
}

std::string ResourceManager::GetAttribute(ResourceType resourceType,
        std::string resourceName,
        std::string attributeGroup,
        std::string attributeName)
{
    ResourceDataType* data = ResourceManager::GetResourceData(resourceType, resourceName);
    if (data == nullptr)
    {
        Log(objectName, resourceName + ": getting attribute failed: resource data not found.", true, true);
        return "";
    }

    // Get attribute index
    unsigned int index = 0;
    while (index < data->attributeTable.size() && (data->attributeTable[index].group != attributeGroup
            || data->attributeTable[index].name != attributeName))
    {
        ++index;
    }

    if (index == data->attributeTable.size())
    {
        Log(objectName, "value could not be got: " + attributeGroup + " " + attributeName + " not found.", true, true);
        return "";
    }

    // Get attribute
    return data->attributeTable[index].value;
}

bool ResourceManager::AddAttribute(ResourceType resourceType,
                                   std::string resourceName,
                                   std::string attributeGroup,
                                   std::string attributeName,
                                   std::string attributeValue)
{
    // Get resource data
    ResourceDataType* data = ResourceManager::GetResourceData(resourceType, resourceName);
    if (data == nullptr)
    {
        Log(objectName, resourceName + ": adding attribute failed: resource data not found.", true, true);
        return false;
    }

    // Add attribute
    data->attributeTable.push_back({ attributeGroup, attributeName, attributeValue });

    return true;
}

bool ResourceManager::ChangeAttribute(ResourceType resourceType,
                                      std::string resourceName,
                                      std::string attributeGroup,
                                      std::string attributeName,
                                      std::string newValue)
{
    // Get resource data
    ResourceDataType* data = ResourceManager::GetResourceData(resourceType, resourceName);
    if (data == nullptr)
    {
        Log(objectName, resourceName + ": changing attribute failed: resource data not found.", true, true);
        return false;
    }

    // Get attribute index
    unsigned int index = 0;
    while (index < data->attributeTable.size() && (data->attributeTable[index].group != attributeGroup
            || data->attributeTable[index].name != attributeName))
    {
        ++index;
    }

    if (index == data->attributeTable.size())
    {
        Log(objectName, "value could not be changed: " + attributeGroup + " " + attributeName + " not found.", true, true);
        return false;
    }

    // Change attribute
    data->attributeTable[index].value = newValue;

    return true;
}

TTF_Font* ResourceManager::GetFont(std::string resourceName)
{
    // Checking if resource is loaded
    if (GetAttribute(RESTYPE_FONT, resourceName, NODE_NAME_FILE, ATTR_NAME_LOADED) != "1" && !LoadFont(resourceName))
    {
        Log(objectName, resourceName + ": resource can't be loaded.", true, true);
        return nullptr;
    }

    std::unordered_map<std::string, TTF_Font*>::iterator fontIterator = fontTable.find(resourceName);
    if (fontIterator == fontTable.end())
    {
        Log(objectName, resourceName + ": resource not found, although marked as loaded.", true, true);
        return nullptr;
    }

    // Returning pointer to the font resource
    return fontIterator->second;
}

SDL_Surface* ResourceManager::GetImage(std::string resourceName)
{
    // Checking if resource is loaded
    if (GetAttribute(RESTYPE_IMAGE, resourceName, NODE_NAME_FILE, ATTR_NAME_LOADED) != "1" && !LoadImage(resourceName))
    {
        Log(objectName, resourceName + ": resource can't be loaded.", true, true);
        return nullptr;
    }

    std::unordered_map<std::string, SDL_Surface*>::iterator imageIterator = imageTable.find(resourceName);
    if (imageIterator == imageTable.end())
    {
        Log(objectName, resourceName + ": resource not found, although marked as loaded.", true, true);
        return nullptr;
    }

    // Returning pointer to the font resource
    return imageIterator->second;
}

ResourceDataType* ResourceManager::GetResourceData(ResourceType resourceType, std::string resourceName)
{
    ResourceDataType* data = nullptr;

    unsigned int index = 0;
    while (index < resourceDatas.size() && (resourceDatas[index].name != resourceName
                                            || resourceDatas[index].type != resourceType))
    {
        ++index;
    }

    if (index != resourceDatas.size())
    {
        data = &resourceDatas[index];
    }

    return data;
}

bool ResourceManager::LoadResourceFile(ResourceType resourceType, std::string resourceName)
{
    bool loadSuccess = true;

    switch (resourceType)
    {
    case RESTYPE_FONT:
        if (!LoadFont(resourceName)) loadSuccess = false;
        break;
    case RESTYPE_IMAGE:
        if (!LoadImage(resourceName)) loadSuccess = false;
        break;
    }

    if (!loadSuccess)
    {
        Log(objectName, resourceName + ": resource file loading has failed.", true, true);
        return false;
    }

    AddAttribute(resourceType, resourceName, NODE_NAME_FILE, ATTR_NAME_LOADED, "1");
    Log(objectName, resourceName + ": resource file is loaded.", true, true);

    return true;
}

bool ResourceManager::LoadFont(std::string resourceName)
{
    std::string value = GetAttribute(RESTYPE_FONT, resourceName, NODE_NAME_FILE, ATTR_NAME_PATH);
    if (value == "") return false;
    std::string fullPath = value;
    value = GetAttribute(RESTYPE_FONT, resourceName, NODE_NAME_FILE, ATTR_NAME_FILE);
    if (value == "") return false;
    fullPath += value;

    value = GetAttribute(RESTYPE_FONT, resourceName, "Font", "size");
    if (value == "") return false;
    int fontSize = std::atoi(value.c_str());

    TTF_Font *font = TTF_OpenFont(fullPath.c_str(), fontSize);
    if (font != nullptr)
    {
        fontTable.emplace(resourceName, font);
        // TODO: Handle logging in case of existing font
        return true;
    }

    Log(objectName, resourceName + ": " + TTF_GetError(), true, true);
    return false;
}

bool ResourceManager::LoadImage(std::string resourceName)
{
    std::string value = GetAttribute(RESTYPE_IMAGE, resourceName, NODE_NAME_FILE, ATTR_NAME_PATH);
    if (value == "") return false;
    std::string fullPath = value;
    value = GetAttribute(RESTYPE_IMAGE, resourceName, NODE_NAME_FILE, ATTR_NAME_FILE);
    if (value == "") return false;
    fullPath += value;

    SDL_Surface *imageSurface = IMG_Load(fullPath.c_str());
    if (imageSurface != nullptr)
    {
        imageTable.emplace(resourceName, imageSurface);
        // TODO: Handle logging in case of existing image
        return true;
    }

    Log(objectName, resourceName + ": " + IMG_GetError(), true, true);
    return false;
}

bool ResourceManager::LoadSound(std::string resourceName)
{
    // TODO: implement loading of sounds

    Log(objectName, "NOT IMPLEMENTED");
    return false;
}
