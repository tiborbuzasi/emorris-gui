/**
 * XML Handler for Resource Manager - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef XML_HANDLER_H
#define XML_HANDLER_H

#include "../../libraries/rapidxml/rapidxml.hpp"
#include "../../libraries/rapidxml/rapidxml_utils.hpp"

#include "ResourceDataType.hpp"
#include "XMLConstants.hpp"


class XMLHandler
{
private:
    /** Object name */
    const std::string objectName = "XMLHandler";

	/** The XML document */
	rapidxml::xml_document<> xmlDocument;

	/** The XML file */
	rapidxml::file<>* xmlFile;

	/** Root node of the XML document */
    rapidxml::xml_node<>* rootNode = nullptr;

    /** Resource data */
    ResourceDataType* data = nullptr;

    /**
     * Get node data
     *
     * @param[in]   node                The node to get the data from
     */
    void GetNodeData(rapidxml::xml_node<>* node);

    /**
     * Get next node
     *
     * @param[in]   node                The node to get the next node
     *
     * @return      The next node
     */
    rapidxml::xml_node<>* GetNextNode(rapidxml::xml_node<>* node);

public:
    /**
     * Destroy XML handler
     */
    ~XMLHandler();

    /**
     * Load XML resource/resource group file
     *
     * @param[in]   path                The path of the XML file
     * @param[in]   name                The name of the XML file (without extension)
     *
     * @return      XML file successfully loaded
     */
    bool LoadXML(std::string path, std::string name);

    /**
     * Load resource name and type
     *
     * @return      Pointer to the resource data
     */
    bool LoadResourceNameAndType();

    /**
     * Load resource data
     */
    void LoadResourceData();

    /**
     * Get resource data
     *
     * @return      Pointer to the resource data
     */
    ResourceDataType* GetResourceData();

    /**
     * Get next resource
     *
     * @return      A next resource exists
     */
    bool GetNextResource();
};

#endif // XML_HANDLER_H
