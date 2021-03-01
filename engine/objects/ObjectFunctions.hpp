/**
 * Object Functions - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef OBJECT_FUNCTIONS_H
#define OBJECT_FUNCTIONS_H

#include "../ObjectManager.hpp"

class ObjectFunctions
{
private:
    /** Object manager */
    static ObjectManager* om;

public:
    /**
     * Initialize object functions
     *
     * @param[in]   objectManager   Pointer to the object manager
     */
    static void Initialize(ObjectManager* objectManager);

	/**
	 * Create object
	 *
	 * @param[in]   resourceName    Name of the object resource
	 */
    static void Create(std::string resourceName);

	/**
	 * Create object
	 *
	 * @param[in]   object          Pointer to the object
	 */
    static void Create(Object* object);

	/**
	 * Destroy object
	 *
	 * @param[in]   objectName      Name of the object
	 */
    static void Destroy(std::string objectName);

	/**
	 * Get object
	 *
	 * @param[in]   objectName      Name of the object
	 *
	 * @return      Pointer to the object
	 */
    static Object* Get(std::string objectName);
};

typedef ObjectFunctions obj;

#endif // OBJECT_FUNCTIONS_H
