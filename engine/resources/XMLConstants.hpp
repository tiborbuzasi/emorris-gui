/**
 * XML Constants - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef XML_CONSTANTS_H
#define XML_CONSTANTS_H

/** Resource data file extension */
const std::string RESDATA_FILE_EXT = ".xml";

/** Node names */
const std::string NODE_NAME_RES = "Resource";
const std::string NODE_NAME_RESGROUP = "ResourceGroup";
const std::string NODE_NAME_INFO = "Info";
const std::string NODE_NAME_DATA = "Data";
const std::string NODE_NAME_FONT = "Font";
const std::string NODE_NAME_IMAGE = "Image";
const std::string NODE_NAME_FILE = "File";

/** Attribute names */
const std::string ATTR_NAME_ENC = "encoding";
const std::string ATTR_NAME_NAME = "name";
const std::string ATTR_NAME_TYPE = "type";
const std::string ATTR_NAME_FILE = "filename";
const std::string ATTR_NAME_PATH = "path";
const std::string ATTR_NAME_LOADED = "loaded";

/** Attribute values */
const std::string ATTR_VAL_UTF8 = "UTF-8";

#endif // XML_CONSTANTS_H
