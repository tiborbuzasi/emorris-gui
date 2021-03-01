/**
 * XML Handler for Resource Manager
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "XMLHandler.hpp"

#include "../UtilityFunctions.hpp"

XMLHandler::~XMLHandler()
{
    delete data;
    delete xmlFile;
}

bool XMLHandler::LoadXML(std::string path, std::string name)
{
    // Create full path
    std::string fullName = path;
    if (path != "")
    {
        fullName += "/";
    }
    fullName += name + RESDATA_FILE_EXT;

    // Open XML file
    try
    {
        xmlFile = new rapidxml::file<>(fullName.c_str());
        xmlDocument.parse<rapidxml::parse_declaration_node | rapidxml::parse_validate_closing_tags> (xmlFile->data());
    }
    // FIXME: seperate catches should be made for seperate exceptions
    catch (...)
    {
        Log(objectName, "loading \"" + fullName + RESDATA_FILE_EXT + "\" failed: " /*+ e.what()*/ + ".", true, true);
        return false;
    }

    // Get XML node
    rapidxml::xml_node<>* node = xmlDocument.first_node();
    if (!node)
    {
        Log(objectName, fullName + ": not a valid XML document.", true, true);
        return false;
    }

    // Get encoding attribute
//     rapidxml::xml_attribute<>* attribute = node->first_attribute(ATTR_NAME_ENC.c_str());
//     if (!attribute || attribute->value() != ATTR_VAL_UTF8)
//     {
//         Log(objectName, fullName + ": XML declaration is incorrect or missing.", true, true);
//         return false;
//     }

    // Set root node to the first resource node
    rootNode = node->next_sibling(NODE_NAME_RESGROUP.c_str());
    if (rootNode)
    {
        rootNode = rootNode->first_node(NODE_NAME_RES.c_str());
    }
    else
    {
        rootNode = node->next_sibling(NODE_NAME_RES.c_str());
    }

    if (!rootNode)
    {
        Log(objectName, fullName + ": " + NODE_NAME_RES + " node not found.", true, true);
        return false;
    }

    return true;
}

bool XMLHandler::LoadResourceNameAndType()
{
    // Initializing data container
    data = new ResourceDataType();
    if (!data)
    {
        Log(objectName, "initializing data container failed.", true, true);
        return false;
    }

    // Get resource name
    rapidxml::xml_attribute<>* attribute = rootNode->first_attribute(ATTR_NAME_NAME.c_str());
    if (!attribute)
    {
        Log(objectName, "resource name attribute not found.", true, true);
        return false;
    }
    data->name = attribute->value();
    std::string resourceName = data->name;

    // Get data node
    rapidxml::xml_node<>* dataNode = rootNode->first_node(NODE_NAME_DATA.c_str());
    if (!dataNode)
    {
        Log(objectName, resourceName + ": " + NODE_NAME_DATA + " node not found.", true, true);
        return false;
    }

    // Get resource type
    attribute = dataNode->first_attribute(ATTR_NAME_TYPE.c_str());
    if (!attribute)
    {
        Log(objectName, resourceName + ": " + ATTR_NAME_TYPE + " attribute not found.", true, true);
        return false;
    }
    std::string resourceTypeString = attribute->value();

    unsigned char index = 0;
    while (index < RESTYPE_NAMES.size() && resourceTypeString != RESTYPE_NAMES.at(index))
    {
        ++index;
    }

    if (index == RESTYPE_NAMES.size())
    {
        Log(objectName, resourceName + ": \"" + resourceTypeString + "\" is an invalid " + ATTR_NAME_TYPE + ".", true, true);
        return false;
    }
    data->type = (ResourceType)(index + 1);

    return true;
}

void XMLHandler::LoadResourceData()
{
    // Get children of data node
    rapidxml::xml_node<>* dataNode = rootNode->first_node(NODE_NAME_DATA.c_str());
    if (!dataNode)
    {
        return;
    }

    rapidxml::xml_node<>* node = dataNode->first_node();
    while (node && node->name() != NODE_NAME_DATA)
    {
        GetNodeData(node);
        node = GetNextNode(node);
    }
}

ResourceDataType* XMLHandler::GetResourceData()
{
    return data;
}

bool XMLHandler::GetNextResource()
{
    rootNode = rootNode->next_sibling(NODE_NAME_RES.c_str());
    if (rootNode)
    {
        return true;
    }

    return false;
}

void XMLHandler::GetNodeData(rapidxml::xml_node<>* node)
{
    // Get resource data attribute group name
    std::string groupName = node->name();
    rapidxml::xml_node<>* parentNode = node->parent();
    while (parentNode && parentNode->name() != NODE_NAME_DATA)
    {
        groupName.insert(0, "-");
        groupName.insert(0, parentNode->name());
        parentNode = parentNode->parent();
    }

    // Get resource data attribute name and value
    rapidxml::xml_attribute<>* attribute = node->first_attribute();
    while (attribute)
    {
        std::string name = attribute->name();
        std::string value = attribute->value();
        data->attributeTable.push_back({ groupName, name, value });
        attribute = attribute->next_attribute();
    }
}


rapidxml::xml_node<>* XMLHandler::GetNextNode(rapidxml::xml_node<>* node)
{
    // Look for children
    rapidxml::xml_node<>* nextNode = node->first_node();
    if (nextNode)
    {
        return nextNode;
    }

    do
    {
        // If node has no children, then look for siblings
        nextNode = node->next_sibling();
        if (nextNode)
        {
            break;
        }

        // If node has no siblings, then look for parent sibling
        nextNode = node->parent();
        node = nextNode;
    }
    while (nextNode && nextNode->name() != NODE_NAME_DATA);

    return nextNode;
}
