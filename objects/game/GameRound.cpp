/**
 * Game round
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "GameRound.hpp"

#include "../Constants.hpp"

GameRound::GameRound(std::string groupName, std::string objectName, unsigned short int x,
                     unsigned short int y, unsigned char gameType) : Object(groupName, objectName, x, y), gameType(gameType) {}

void GameRound::Create()
{
    // Create game
    game = new Game();

    // Load game resources
    res::Load("Game", "images");

    // Draw game board
    SetTexture("GameBoard");

    // Calculate field positions
    CalculateFieldPositions();

    // Subscribe to mouse and keyboard input events
    input::Add(INPUT_MOUSE, this);
    input::Add(INPUT_KEYBOARD, this);
    input::Add(INPUT_CONTROLLER, this);

    bool spectator = false;
    if (gameType == 0)
    {
        spectator = true;
    }

//     if (gameType == 1 || gameType == 2)
    {
        players[1] = new LearningAI();
        if (!players[1]->Initialize(game, spectator))
        {
            Log(GetName(), "creating AI failed, switching to human for player 2", true);
            delete players[1];
            players[1] = nullptr;
        };
        players[1]->Load("storage/learningAI" + std::to_string(1) + ".mai");
    }

    if (gameType == 1)
    {
        spectator = true;
    }
//     if (gameType == 2)
    {
        players[0] = new LearningAI();
        if (!players[0]->Initialize(game, spectator))
        {
            Log(GetName(), "creating AI failed, switching to human for player 1", true);
            delete players[0];
            players[0] = nullptr;
        };
        players[0]->Load("storage/learningAI" + std::to_string(0) + ".mai");
    }

}

void GameRound::Destroy()
{
    for (unsigned char place = 0; place < NUM_OF_FIELD_PLACES; ++place)
    {
        obj::Destroy("piece" + std::to_string(place));
    }

    input::Remove(INPUT_MOUSE, GetName());
    input::Remove(INPUT_KEYBOARD, GetName());
    input::Remove(INPUT_CONTROLLER, GetName());

    delete game;

}

void GameRound::Update()
{
    if (game->GetGameState() == GameState::End && !gameEnded)
    {
        if (game->GetCurrentPlayer() == 1)
        {
            if (players[0] != nullptr)
            {
                players[0]->Store(true);
            }
            if (players[1] != nullptr)
            {
                players[1]->Store(false);
            }
        }
        else
        {
            if (players[0] != nullptr)
            {
                players[0]->Store(false);
            }
            if (players[1] != nullptr)
            {
                players[1]->Store(true);
            }
        }
        if (players[0] != nullptr)
        {
            players[0]->Save("storage/learningAI" + std::to_string(0) + ".mai");
        }
        if (players[1] != nullptr)
        {
            players[1]->Save("storage/learningAI" + std::to_string(1) + ".mai");
        }
        gameEnded = true;
    }

    if (gameEnded)
    {
        return;
    }

    if (players[game->GetCurrentPlayer() - 1] != nullptr)
    {
        if (players[game->GetCurrentPlayer() - 1]->IsSpectator())
        {
            players[game->GetCurrentPlayer() - 1]->GetNextStep();
        }
        else
        {
            // AI step
            SetAISelectedPlace();
            SetPosition(&selectedFieldPosition);
            SDL_Delay(1000);
        }
   }

    if (selectedFieldPosition.zIndex == INVALID_POS)
    {
        return;
    }

    // Take action based on the game state
    switch (game->GetGameState())
    {
    case GameState::Place:
        PlacePiece(selectedFieldPosition);
        break;
    case GameState::Remove:
        RemovePiece(selectedFieldPosition);
        break;
    case GameState::Move:
        MovePiece(selectedFieldPosition);
        break;
    }

    ResetPosition(&selectedFieldPosition);
}

void GameRound::Draw()
{
    // Draw the move from selection marker
    if (lastFieldPosition.zIndex != INVALID_POS)
    {
        draw::Sprite("MoveFromMarker" + std::to_string(lastFieldPosition.zIndex), "BlueFieldSelectionMarker",
                     lastFieldPosition.x, lastFieldPosition.y, ZINDEX_FIRST, ALIGN_NONE, ALIGN_NONE);
    }

    // Draw the field selection marker
    if (inputSelectionMarker.zIndex != INVALID_POS)
    {
        draw::Sprite("SelectionMarker" + std::to_string(inputSelectionMarker.zIndex), "YellowFieldSelectionMarker",
                     inputSelectionMarker.x, inputSelectionMarker.y, ZINDEX_FIRST, ALIGN_NONE, ALIGN_NONE);
    }

    // Draw the current player
    std::string player = "Player ";
    switch(game->GetCurrentPlayer())
    {
    case 1:
        player += "1 (Red)";
        break;
    case 2:
        player += "2 (Green)";
        break;
    }
    if (game->GetGameState() != GameState::End)
    {
        draw::Text(player, "TextFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 4, ZINDEX_LAST, ALIGN_CENTER,
                   ALIGN_CENTER);
    }
    else
    {
        draw::Text("The winner is " + player + "!", "TextFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 4,
                   ZINDEX_LAST, ALIGN_CENTER, ALIGN_CENTER);
    }

    // Draw the game state text
    std::string gameState;
    switch (game->GetGameState())
    {
    case GameState::Place:
        gameState = "Place piece";
        break;
    case GameState::Remove:
        gameState = "Remove piece";
        break;
    case GameState::Move:
        gameState = "Move piece";
        break;
    case GameState::End:
        gameState = "Game Over";
        break;
    default:
        gameState = "";
        break;
    }
    draw::Text(gameState, "TextFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 2, ZINDEX_LAST,
               ALIGN_CENTER, ALIGN_CENTER);
}

void GameRound::Input(SDL_Event event)
{
    if ((players[game->GetCurrentPlayer() - 1]) != nullptr && !players[game->GetCurrentPlayer() - 1]->IsSpectator())
    {
        return;
    }

    bool takeAction = false;
    if (game->GetGameState() == GameState::End)
    {
        ResetPosition(&inputSelectionMarker);
        return;
    }

    // Handle mouse click event
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        ResetPosition(&selectedFieldMap);
        SetPosition(&inputSelectionMarker, event.button.x, event.button.y);
        takeAction = true;
        Log(GetName(), "mouse clicked on field position " + std::to_string(inputSelectionMarker.zIndex) + ".", true, true);
    }

    // Get mouse state
    MouseState mouseState = input::GetMouseState();
    if (mouseState.positionChanged && !takeAction)
    {
        ResetPosition(&selectedFieldMap);
        ResetPosition(&inputSelectionMarker);
        SetPosition(&inputSelectionMarker, mouseState.x, mouseState.y);
    }

    // Handle keyboard event
    if (event.type == SDL_KEYDOWN && !takeAction)
    {
        KeyboardInput(&event);
        SetPosition(&inputSelectionMarker);
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            Log(GetName(), "action keyboard key on field position " + std::to_string(inputSelectionMarker.zIndex) + ".", true, true);
            takeAction = true;
        }
    }

    // Handle controller event
    if (event.type == SDL_CONTROLLERBUTTONDOWN && !takeAction)
    {
        GamepadInput(&event);
        SetPosition(&inputSelectionMarker);
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
        {
            Log(GetName(), "action controller key on field position " + std::to_string(inputSelectionMarker.zIndex) + ".", true, true);
            takeAction = true;
        }
    }

    selectedFieldPosition = inputSelectionMarker;
    if (!takeAction)
    {
        ResetPosition(&selectedFieldPosition);
    }
}

void GameRound::KeyboardInput(SDL_Event* event)
{
    // Set default position
    if (selectedFieldMap.zIndex == INVALID_POS)
    {
        selectedFieldMap.x = MAP_SIZE / 2 + 1;
        selectedFieldMap.y = selectedFieldMap.x;
    }

    // Change selected field place
    unsigned char coordinates[2] = { selectedFieldMap.x, selectedFieldMap.y };
    switch (event->key.keysym.sym)
    {
    case SDLK_LEFT:
        if (selectedFieldMap.x > 1)
        {
            --selectedFieldMap.x;
            while (selectedFieldMap.x > 1 && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                --selectedFieldMap.x;
            }
        }
        break;
    case SDLK_RIGHT:
        if (selectedFieldMap.x < MAP_SIZE)
        {
            ++selectedFieldMap.x;
            while  (selectedFieldMap.x < MAP_SIZE && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                ++selectedFieldMap.x;
            }
        }
        break;
    case SDLK_UP:
        if (selectedFieldMap.y > 1)
        {
            --selectedFieldMap.y;
            while (selectedFieldMap.y > 1 && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                --selectedFieldMap.y;
            }
        }
        break;
    case SDLK_DOWN:
        if (selectedFieldMap.y < MAP_SIZE)
        {
            ++selectedFieldMap.y;
            while  (selectedFieldMap.y < MAP_SIZE && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                ++selectedFieldMap.y;
            }
        }
        break;
    }

    if (SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
    {
        selectedFieldMap.x = coordinates[0];
        selectedFieldMap.y = coordinates[1];
    }

    selectedFieldMap.zIndex = SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1];
    inputSelectionMarker.zIndex = selectedFieldMap.zIndex;
}

void GameRound::GamepadInput(SDL_Event* event)
{
    // Set default position
    if (selectedFieldMap.zIndex == INVALID_POS)
    {
        selectedFieldMap.x = MAP_SIZE / 2 + 1;
        selectedFieldMap.y = selectedFieldMap.x;
    }

    // Change selected field place
    unsigned char coordinates[2] = { selectedFieldMap.x, selectedFieldMap.y };

    switch (event->cbutton.button)
    {
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        if (selectedFieldMap.x > 1)
        {
            --selectedFieldMap.x;
            while (selectedFieldMap.x > 1 && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                --selectedFieldMap.x;
            }
        }
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        if (selectedFieldMap.x < MAP_SIZE)
        {
            ++selectedFieldMap.x;
            while  (selectedFieldMap.x < MAP_SIZE && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                ++selectedFieldMap.x;
            }
        }
        break;
    case  SDL_CONTROLLER_BUTTON_DPAD_UP:
        if (selectedFieldMap.y > 1)
        {
            --selectedFieldMap.y;
            while (selectedFieldMap.y > 1 && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                --selectedFieldMap.y;
            }
        }
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        if (selectedFieldMap.y < MAP_SIZE)
        {
            ++selectedFieldMap.y;
            while  (selectedFieldMap.y < MAP_SIZE && SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
            {
                ++selectedFieldMap.y;
            }
        }
        break;
    }

    if (SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1] == INVALID_POS)
    {
        selectedFieldMap.x = coordinates[0];
        selectedFieldMap.y = coordinates[1];
    }

    selectedFieldMap.zIndex = SQUARE_MAP[selectedFieldMap.x - 1][selectedFieldMap.y - 1];
    inputSelectionMarker.zIndex = selectedFieldMap.zIndex;
}

void GameRound::CalculateFieldPositions()
{
    Position position;

    const unsigned char CENTER = MAP_SIZE / 2;
    for (unsigned int s = NUM_OF_SQUARES; s > 0; --s)
    {
        const unsigned char LIMIT = CENTER + s + 1;
        for (int x = CENTER - s; x < LIMIT; x = x + s)
        {
            for (int y = CENTER - s; y < LIMIT; y = y + s)
            {
                if (x == CENTER && y == CENTER)
                {
                    continue;
                }

                position.x = GetPosition().x + (x - CENTER) * 2 * BLOCK_SIZE;
                position.y = GetPosition().y + (y - CENTER) * 2 * BLOCK_SIZE;
                position.zIndex = SQUARE_MAP[x][y];

                fieldPositions.push_back(position);
            }
        }
    }
}

void GameRound::SetPosition(Position* position, unsigned short int inputX, unsigned short int inputY)
{
    if (position == nullptr)
    {
        Log(GetName(), "position calculation failed.", true, true);
        return;
    }

    std::vector<Position>::iterator pi;
    for (pi = fieldPositions.begin(); pi != fieldPositions.end(); ++pi)
    {
        if (inputX != 0 || inputY != 0)
        {
            if (inputX >= pi->x - BLOCK_SIZE / 2
                    && inputX < pi->x + BLOCK_SIZE / 2
                    && inputY >= pi->y - BLOCK_SIZE / 2
                    && inputY < pi->y + BLOCK_SIZE / 2)
            {
                position->zIndex = pi->zIndex;
            }
        }

        // Return if position coordinates for given field position are calculated
        if (position->zIndex == pi->zIndex)
        {
            break;
        }
    }

    // Set window coordinates for position
    if (pi != fieldPositions.end())
    {
        position->x = pi->x;
        position->y = pi->y;
    }
}

void GameRound::ResetPosition(Position* position)
{
    if (!position)
    {
        Log(GetName(), "position calculation failed.", true, true);
        return;
    }

    position->zIndex = INVALID_POS;
    position->x = 0;
    position->y = 0;
}

void GameRound::PlacePiece(Position position)
{
    if (!game->Place(position.zIndex))
    {
        if (players[game->GetCurrentPlayer() - 1] == nullptr || players[game->GetCurrentPlayer() - 1]->IsSpectator())
        {
            return;
        }
        while (!game->Place(selectedFieldPosition.zIndex))
        {
            SetAISelectedPlace(true);
        }
        SetPosition(&selectedFieldPosition);
    }
    // Register AI step
    if (players[game->GetCurrentPlayer() - 1] != nullptr)
    {
        players[game->GetCurrentPlayer() - 1]->Register({ INVALID_POS, selectedFieldPosition.zIndex });
    }

    obj::Create(new GamePiece("game", "piece" + std::to_string(selectedFieldPosition.zIndex), game->GetCurrentPlayer(),
                              selectedFieldPosition.x, selectedFieldPosition.y));
    Log(GetName(), "Player " + std::to_string(game->GetCurrentPlayer()) + " placed a piece to position "
        + std::to_string(position.zIndex) + ".", true, true);
    game->CheckState();
}

void GameRound::RemovePiece(Position position)
{
    if (!game->Remove(position.zIndex))
    {
        if (players[game->GetCurrentPlayer() - 1] == nullptr || players[game->GetCurrentPlayer() - 1]->IsSpectator())
        {
            return;
        }
        while (!game->Remove(selectedFieldPosition.zIndex))
        {
            SetAISelectedPlace(true);
        }
        SetPosition(&selectedFieldPosition);
    }
    // Register AI step
    if (players[game->GetCurrentPlayer() - 1] != nullptr)
    {
        players[game->GetCurrentPlayer() - 1]->Register({ selectedFieldPosition.zIndex, INVALID_POS });
    }

    obj::Destroy("piece" + std::to_string(selectedFieldPosition.zIndex));
    Log(GetName(), "Player " + std::to_string(game->GetCurrentPlayer()) + " removed a piece from position "
        + std::to_string(position.zIndex) + ".", true, true);
    game->CheckState();
}

void GameRound::MovePiece(Position position)
{
    if ((lastFieldPosition.zIndex != INVALID_POS || !game->Move(position.zIndex, lastFieldPosition.zIndex))
            && (lastFieldPosition.zIndex == INVALID_POS || !game->Move(lastFieldPosition.zIndex, position.zIndex)))
    {
        if (players[game->GetCurrentPlayer() - 1] == nullptr || players[game->GetCurrentPlayer() - 1]->IsSpectator())
        {
            if (lastFieldPosition.zIndex != INVALID_POS)
            {
                ResetPosition(&lastFieldPosition);
            }
            return;
        }
        while (!game->Move(lastFieldPosition.zIndex, selectedFieldPosition.zIndex))
        {
            SetAISelectedPlace(true);
        }
        SetPosition(&selectedFieldPosition);
    }
    // Register AI step
    if (players[game->GetCurrentPlayer() - 1] != nullptr)
    {
        players[game->GetCurrentPlayer() - 1]->Register({ lastFieldPosition.zIndex, selectedFieldPosition.zIndex });
    }

    // Move from position
    if (lastFieldPosition.zIndex == INVALID_POS)
    {
        lastFieldPosition = position;
        SetPosition(&lastFieldPosition);
    }
    // Move to position
    else
    {
        obj::Destroy("piece" + std::to_string(lastFieldPosition.zIndex));
        obj::Create(new GamePiece("game", "piece" + std::to_string(selectedFieldPosition.zIndex), game->GetCurrentPlayer(),
                                  selectedFieldPosition.x, selectedFieldPosition.y));
        Log(GetName(), "Player " + std::to_string(game->GetCurrentPlayer()) + " moved a piece from position " + std::to_string(
                lastFieldPosition.zIndex) + " to position " + std::to_string(position.zIndex) + ".", true, true);

        ResetPosition(&lastFieldPosition);
        game->CheckState();
    }
}

void GameRound::SetAISelectedPlace(bool retry)
{
    std::array<unsigned char, 2> changes = players[game->GetCurrentPlayer() - 1]->GetNextStep(retry);

    switch (game->GetGameState())
    {
    case GameState::Place:
        selectedFieldPosition.zIndex = changes[1];
        break;
    case GameState::Remove:
        selectedFieldPosition.zIndex = changes[0];
        break;
    case GameState::Move:
        lastFieldPosition.zIndex = changes[0];
        SetPosition(&lastFieldPosition);
        selectedFieldPosition.zIndex = changes[1];
        break;
    }
}
