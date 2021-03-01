/**
 * Resource Data Type - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef RESOURCE_DATA_TYPE_H
#define RESOURCE_DATA_TYPE_H

#include <vector>

#include "AttributesType.hpp"
#include "ResourceType.hpp"

struct ResourceDataType
{
    ResourceType type;
    std::string name;
    std::vector<AttributeType> attributeTable;
};

#endif // RESOURCE_DATA_TYPE_H
