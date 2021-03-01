/**
 * Game round - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef GAME_ROUND_H
#define GAME_ROUND_H

#include "Game.hpp"
#include "LearningAI.hpp"

#include "../../engine/objects/ObjectIncludes.hpp"
#include "GamePiece.hpp"

class GameRound : public Object
{
private:
    /** Invalid position */
    const unsigned char INVALID_POS = 255;

    /** Mapping of the game square
     *  0	255	255	1	255	255	2
     *  255	8	255	9	255	10	255
     *  255	255	16	17	18	255	255
     *  7	15	23	255	19	11	3
     *  255	255	22	21	20	255	255
     *  255	14	255	13	255	12	255
     *  6	255	255	5	255	255	4
     */
    const unsigned char SQUARE_MAP[7][7] =
    {
        { 0, INVALID_POS, INVALID_POS, 7, INVALID_POS, INVALID_POS, 6 },
        { INVALID_POS, 8, INVALID_POS, 15, INVALID_POS, 14, INVALID_POS },
        { INVALID_POS, INVALID_POS, 16, 23, 22, INVALID_POS, INVALID_POS },
        { 1, 9, 17, INVALID_POS, 21, 13, 5 },
        { INVALID_POS, INVALID_POS, 18, 19, 20, INVALID_POS, INVALID_POS },
        { INVALID_POS, 10, INVALID_POS, 11, INVALID_POS, 12, INVALID_POS },
        { 2, INVALID_POS, INVALID_POS, 3, INVALID_POS, INVALID_POS, 4 }
    };

    /** Size of the game square map */
    const unsigned char MAP_SIZE = 7;

    /** @brief Game type
     * 0 - human vs. human
     * 1 - human vs. AI
     * 2 - AI vs. AI
     */
    unsigned char gameType;

    /** @brief AI Players
     * If player->at() is nullptr, then the player is human
     */
    LearningAI* players[NUM_OF_PLAYERS] = { nullptr };

    /** Game ended */
    bool gameEnded = false;
    bool skipAIUpdate = false;

    /** @brief Field positions
     * The field position is stored in the z-index member,
     * and the screen coordinates in the x and y members.
     */
    std::vector<Position> fieldPositions;

    /** @brief Selected field position
     * The field place is stored in the z-index member,
     * and the position in the mapping is stored
     * in the x (column) and y (row) members.
     */
    Position selectedFieldPosition = { INVALID_POS };

    /** Selected field position (for keyboard) */
    Position selectedFieldMap = { INVALID_POS };

    /** @brief Last field position (for the piece moving function)
     * The field place is stored in the z-index member,
     * and the position in the mapping is stored
     * in the x (column) and y (row) members.
     */
    Position lastFieldPosition = { INVALID_POS };

    /** @brief Input selection marker
     * The field place is stored in the z-index member,
     * and the position in the mapping is stored
     * in the x (column) and y (row) members.
     */
    Position inputSelectionMarker = { INVALID_POS };

    /**
     * Set AI selected place
     *
     * @param[in] retry Retry getting AI selected place
     */
    void SetAISelectedPlace(bool retry = false);


public:
    /** eMorris game logic object */
    Game* game = nullptr;

    /**
     * Construct object
     *
     * @param[in]   groupName           The name of the texture group
     * @param[in]   objectName          The name of the object
     * @param[in]   x                   X coordinate of the position (0 by default)
     * @param[in]   y                   Y coordinate of the position (0 by default)
     */
    GameRound(std::string groupName, std::string objectName, unsigned short int x = 0, unsigned short y = 0, unsigned char gameType = 0);

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
     *
     * @param[in]   event               Input event
     */
    void Input(SDL_Event event);

    /**
     * Keyboard input
     *
     * @param[in]   event               Pointer to the input event
     */
    void KeyboardInput(SDL_Event* event);

    /**
     * Gamepad input
     *
     * @param[in]   event               Pointer to the input event
     */
    void GamepadInput(SDL_Event* event);

    /**
     * @brief Calculate field positions' coordinates
     *
     * Calculates the window position coordinates of the field places
     * (stored in the x and y member), and also assigns them
     * to the field place (stored in the zIndex member).
     */
    void CalculateFieldPositions();

    /**
     * Calculate field position coordiantes
     *
     * Calculates the window position of the piece,
     * and also the position of the piece in the game field,
     * if mouse input is given as the x and y member.
     * If the game field position is not known, give it the value INVALID_POS.
     * The window position coordinates are stored in
     * the x and y member of the position structure,
     * while the game field value is stored in the z-index member.
     *
     * @param[out]  position            The game field position and position coordiantes
     * @param[in]   x                   X coordinate of the mouse position
     * @param[in]   y                   Y coordinate of the mouse position
     */
    void SetPosition(Position* position, unsigned short int inputX = 0, unsigned short int inputY = 0);

    /**
     * Reset field position
     *
     * @param[out]  position            The game field position and position coordiantes
     */
    void ResetPosition(Position* position);

    /**
     * Place piece
     *
     * @param[in]   position            Position to place the piece to
     */
    void PlacePiece(Position position);

    /**
     * Remove piece
     *
     * @param[in]   position            Position to remove the piece from
     */
    void RemovePiece(Position position);

    /**
     * Move piece
     *
     * @param[in]   position            Position to move from or move to
     */
    void MovePiece(Position position);
};

#endif // GAME_ROUND_H
