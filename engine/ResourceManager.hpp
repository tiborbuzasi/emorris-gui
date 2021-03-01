/**
 * Resource Manager - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <array>
#include <string>
#include <unordered_map>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "resources/ResourceDataType.hpp"
#include "resources/ResourceType.hpp"

class ResourceManager
{
private:
    /** Object name */
    const std::string objectName = "ResourceManager";

    /** Vector of resource data */
    std::vector<ResourceDataType> resourceDatas;

    /** List of font resources */
    std::unordered_map<std::string, TTF_Font*> fontTable;

    /** List of image resources */
    std::unordered_map<std::string, SDL_Surface*> imageTable;

    /**
     * Get resource data
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
     *
     * @return      The resource data
     */
    ResourceDataType* GetResourceData(ResourceType resourceType, std::string resourceName);

    /**
     * Load resource file
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
     *
     * @return      Resource file successfully loaded
     */
    bool LoadResourceFile(ResourceType resourceType, std::string resourceName);

    /**
     * Load font resource file
     *
     * @param[in]   resourceName        The name of the font resource
     *
     * @return      Font resource file successfully loaded
     */
    bool LoadFont(std::string resourceName);

    /**
     * Load image resource file
     *
     * @param[in]   resourceName        The name of the image resource
     *
     * @return      Image resource file successfully loaded
     */
    bool LoadImage(std::string resourceName);

    /**
     * Load sound resource file
     *
     * @param[in]   resourceName        The name of the sound resource
     *
     * @return      Sound resource file successfully loaded
     */
    bool LoadSound(std::string resourceName);

public:
    /**
     * Load resource
     *
     * @param[in]   resourceName        The name of the resource
     * @param[in]   resourcePath        The path of the resource (default is empty)
     * @param[in]   reload              Force to reload loaded resources (default is false)
     */
    bool LoadResource(std::string resourceName, std::string resourcePath = "", bool reload = false);

    /**
     * Unload resource
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
	 */
    void UnloadResource(ResourceType resourceType, std::string resourceName);


    /**
     * Get resource data attribute
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
     * @param[in]   attributeGroup      The group of the attribute
     * @param[in]   attributeName       The name of the attribute
     *
     * @return  The value of the attribute
     */
    std::string GetAttribute(ResourceType resourceType,
                             std::string resourceName,
                             std::string attributeGroup,
                             std::string attributeName);

    /**
     * Add resource data attribute
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
     * @param[in]   attributeGroup      The group of the attribute
     * @param[in]   attributeName       The name of the attribute
     * @param[in]   attributeValue      The value of the attribute
     */
    bool AddAttribute(ResourceType resourceType,
                      std::string resourceName,
                      std::string attributeGroup,
                      std::string attributeName,
                      std::string attributeValue);

    /**
     * Change resource data attribute
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
     * @param[in]   attributeGroup      The group of the attribute
     * @param[in]   attributeName       The name of the attribute
     * @param[in]   newValue            New value of the attribute
     *
     * @return  Attribute value successfully changed
     */
    bool ChangeAttribute(ResourceType resourceType,
                         std::string resourceName,
                         std::string attributeGroup,
                         std::string attributeName,
                         std::string newValue);

    /**
     * Get font resource data
     *
     * @param[in]   resourceName        The name of the image resource
     * @param[in]   fontSize            Size of the font to load in points
     *
     * @return      Pointer to the font resource data
     */
    TTF_Font* GetFont(std::string resourceName);

    /**
     * Get image resource data
     *
     * @param[in]   resourceName        The name of the image resource
     *
     * @return      Pointer to the image resource data
     */
    SDL_Surface* GetImage(std::string resourceName);
};

#endif // RESOURCE_MANAGER_H
