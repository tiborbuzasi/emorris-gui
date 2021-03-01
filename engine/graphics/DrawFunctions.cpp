/**
 * Draw Functions
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "DrawFunctions.hpp"

#include "../UtilityFunctions.hpp"

GraphicsHandler* DrawFunctions::gh = nullptr;

void DrawFunctions::Initialize(GraphicsHandler* graphicsHandler)
{
    gh = graphicsHandler;
    if (gh == nullptr)
    {
        Log("Draw functions", "initialization failed: GraphicsHandler not found.", true, true);
        exit(1);
    }

    // Create texture group for the draw functions
    gh->CreateGroup(DRAW_GROUP_NAME, ZINDEX_LAST);
}

void DrawFunctions::Lock(std::string textureName, bool lock)
{
    gh->LockTexture(DRAW_GROUP_NAME, textureName, lock);
}

void DrawFunctions::Sprite(std::string textureName,
                           std::string resourceName,
                           unsigned short int positionX,
                           unsigned short int positionY,
                           unsigned char zIndex,
                           AlignmentType horizontalAlignment,
                           AlignmentType verticalAlignment)
{
    gh->DrawSprite(DRAW_GROUP_NAME, textureName, resourceName, positionX, positionY, zIndex, horizontalAlignment,
                   verticalAlignment, true);
}

void DrawFunctions::Text(std::string text,
                         std::string fontName,
                         SDL_Color color,
                         unsigned short int positionX,
                         unsigned short int positionY,
                         unsigned char zIndex,
                         AlignmentType horizontalAlignment,
                         AlignmentType verticalAlignment)
{
    gh->DrawText(DRAW_GROUP_NAME, text, fontName, color, positionX, positionY, zIndex, horizontalAlignment,
                 verticalAlignment, true);
}
