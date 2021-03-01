/**
 * Menu controller
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "MenuController.hpp"

#include "../AppInfo.hpp"
#include "Constants.hpp"
#include "game/GameRound.hpp"

MenuController::MenuController(std::string groupName, std::string objectName) : Object(groupName, objectName) {}

void MenuController::Create()
{
    res::Load("Junction", "fonts");
    input::Add(INPUT_KEYBOARD, this);
    input::Add(INPUT_CONTROLLER, this);

    // Draw application info
    std::string versionInfo = APP_NAME;
    versionInfo += " ";
    versionInfo += APP_VERSION;
    draw::Text(versionInfo, "NoteFont", COLOR_WHITE, BLOCK_SIZE, CANVAS_HEIGHT - BLOCK_SIZE, ZINDEX_LAST, ALIGN_LEFT,
               ALIGN_CENTER);
    draw::Lock(DRAW_TEXT_RES_PREFIX + versionInfo, true);
}

void MenuController::Destroy()
{
    input::Remove(INPUT_KEYBOARD, GetName());
    input::Remove(INPUT_CONTROLLER, GetName());
}

void MenuController::Update()
{
}

void MenuController::Draw()
{
    switch (menuId)
    {
    case 0:
        std::string gameModeString = "";
        switch (gameMode)
        {
            case 0:
                gameModeString = "Human vs. Human";
                break;
            case 1:
                gameModeString = "Human vs. AI";
                break;
            case 2:
                gameModeString = "AI vs. AI";
                break;
        }
        draw::Text("eMorris", "TitleFont", COLOR_WHITE, CANVAS_WIDTH / 2, BLOCK_SIZE * 4, ZINDEX_LAST, ALIGN_CENTER,
                   ALIGN_CENTER);
        draw::Text(gameModeString, "TitleFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 12,
                   ZINDEX_LAST, ALIGN_CENTER, ALIGN_CENTER);
        draw::Text("Press Left or Right to select game mode", "TextFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 6,
                   ZINDEX_LAST, ALIGN_CENTER, ALIGN_CENTER);
        draw::Text("Press Space to start game", "TextFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 4,
                   ZINDEX_LAST, ALIGN_CENTER, ALIGN_CENTER);
        draw::Text("Press Escape to quit", "TextFont", COLOR_WHITE, CANVAS_WIDTH / 2, CANVAS_HEIGHT - BLOCK_SIZE * 2,
                   ZINDEX_LAST, ALIGN_CENTER, ALIGN_CENTER);
        break;
    }
}

void MenuController::Input(SDL_Event event)
{
    if (event.type != SDL_KEYDOWN && event.type != SDL_CONTROLLERBUTTONDOWN)
    {
        return;
    }

    if (menuId == 0)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE || event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
        {
            Log(GetName(), "user pressed the Escape key on the keyboard.");
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
            return;
        }
        else if (event.key.keysym.sym == SDLK_SPACE || event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
        {
            Log(GetName(), "user pressed the Space key on the keyboard.");
            obj::Create(new GameRound("controllers", "GameRound", CENTER_X, CENTER_Y - BLOCK_SIZE * 2, gameMode));
            menuId = 10;
        }
        else if (menuId == 0 && event.key.keysym.sym == SDLK_LEFT || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
        {
            Log(GetName(), "user pressed the left key on the keyboard.");
            if (gameMode == 0)
            {
                gameMode = 2;
            }
            else
            {
                --gameMode;
            }
        }
        else if (menuId == 0 && event.key.keysym.sym == SDLK_RIGHT || event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
        {
            Log(GetName(), "user pressed the right key on the keyboard.");
            if (gameMode == 2)
            {
                gameMode = 0;
            }
            else
            {
                ++gameMode;
            }
        }
    }
    else if (menuId == 10)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE || event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
        {
            Log(GetName(), "user pressed the Space key on the keyboard.");
            obj::Destroy("GameRound");
            menuId = 0;
        }
    }
}

void MenuController::Execute()
{

}
