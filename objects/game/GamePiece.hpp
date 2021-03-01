/**
 * Game piece - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef GAME_PIECE_H
#define GAME_PIECE_H

#include "../../engine/objects/ObjectIncludes.hpp"

#include "Game.hpp"

class GamePiece : public Object
{
private:
    /** Player ID */
    const unsigned char playerId;

public:
    /**
     * Construct object
     *
     * @param[in]   groupName           The name of the texture group
     * @param[in]   objectName          The name of the object
     * @param[in]   playerID            The ID of the player used in the game logic
     * @param[in]   x                   X coordinate of the position (0 by default)
     * @param[in]   y                   Y coordinate of the position (0 by default)
     */
    GamePiece(std::string groupName, std::string objectName, unsigned char playerId, unsigned short int x,
              unsigned short int y);

    /**
     * Create object
     */
    void Create();

    /**
     * Destroy object
     */
    void Destroy();

    /**
     * Update object
     */
    void Update();

    /**
     * Draw object
     */
    void Draw();

    /**
     * Handle inputs
     */
    void Input(SDL_Event event);
};

#endif // GAME_PIECE_H
