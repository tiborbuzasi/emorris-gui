/**
 * Game piece
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "GamePiece.hpp"

#include "../Constants.hpp"

GamePiece::GamePiece(std::string groupName, std::string objectName, unsigned char playerId, unsigned short int x,
                     unsigned short int y) : Object(groupName, objectName, x, y), playerId(playerId) {}

void GamePiece::Create()
{
    // Set game piece texture
    switch (playerId)
    {
    case 1:
        SetTexture("RedPiece");
        break;
    case 2:
        SetTexture("GreenPiece");
        break;
    default:
        Log(GetName(), "invalid player ID \"" + std::to_string(playerId) + "\".");
        break;
    }
}

void GamePiece::Destroy()
{

}

void GamePiece::Update()
{

}

void GamePiece::Draw()
{

}

void GamePiece::Input(SDL_Event event)
{

}


