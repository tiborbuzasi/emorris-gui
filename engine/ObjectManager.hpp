/**
 * Object Manager - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "InterfaceManager.hpp"
#include "objects/Object.hpp"

class ObjectManager
{
private:
    /** Object name */
    const std::string objectName = "ObjectManager";

    /** Interface manager */
    InterfaceManager* im = nullptr;

    /** Vector of objects */
    std::vector<Object*> objects;

public:
    /**
     * Creating the object manager
     *
     * @param[in]   interfaceManager Pointer to the interface manager
     */
    ObjectManager(InterfaceManager* interfaceManager);

	/**
	 * Create object
	 *
	 * @param[in]   object          Pointer to the object
	 */
    void CreateObject(Object* object);

	/**
	 * Destroy object
	 *
	 * @param[in]   objectName      Name of the object
	 */
    void DestroyObject(std::string objectName);

	/**
	 * Get object
	 *
	 * @param[in]   objectName      Name of the object
	 *
	 * @return      Pointer to the object
	 */
    Object* GetObject(std::string objectName);

    /**
	 * Update objects
	 */
    void Update();

    /**
	 * Draw objects
	 */
    void Draw();

};

#endif // OBJECT_MANAGER_H
