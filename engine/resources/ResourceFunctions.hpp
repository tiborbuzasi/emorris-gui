/**
 * Resource Functions - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef RESOURCE_FUNCTIONS_H
#define RESOURCE_FUNCTIONS_H

#include "../ResourceManager.hpp"

class ResourceFunctions
{
private:
    /** Resource manager */
    static ResourceManager* rm;

public:
    /**
     * Initialize resource functions
     *
     * @param[in]   objectManager   Pointer to the resource manager
     */
    static void Initialize(ResourceManager* resourceManager);

    /**
     * Load resource
     *
     * @param[in]   resourceName        The name of the resource
     * @param[in]   resourcePath        The path of the resource (default is empty)
     */
    static void Load(std::string resourceName, std::string resourcePath = "");

    /**
     * Unload resource
     *
     * @param[in]   resourceType        The type of the resource
     * @param[in]   resourceName        The name of the resource
     */
    static void Unload(ResourceType resourceType, std::string resourceName);

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
    static std::string GetAttribute(ResourceType resourceType,
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
    static bool AddAttribute(ResourceType resourceType,
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
     */
    static bool ChangeAttribute(ResourceType resourceType,
                                std::string resourceName,
                                std::string attributeGroup,
                                std::string attributeName,
                                std::string newValue);

};

typedef ResourceFunctions res;

#endif // RESOURCE_FUNCTIONS_H
