/**
 * Graphics Handler for Interface Manager
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#include "GraphicsHandler.hpp"

#include "../UtilityFunctions.hpp"

GraphicsHandler::GraphicsHandler(ResourceManager* resourceManager, SDL_Window* window)
{
    // Set pointer to resource manager
    rm = resourceManager;

    if (rm == nullptr)
    {
        Log(objectName, "initialization failed: ResourceManager not found.", true, true);
        exit(1);
    }

    // Create renderer
//     SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
//     Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    if (rm->GetAttribute(RESTYPE_SETTINGS, "Settings", "Video", "vSync") == "1")
    {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if (renderer == nullptr)
    {
        Log(objectName, SDL_GetError(), true, true);
        exit(1);
    }

    // Get renderer info
    SDL_RendererInfo rendererInfo;
    if (SDL_GetRendererInfo(renderer, &rendererInfo) < 0)
    {
        Log(objectName, SDL_GetError(), true, true);
        exit(1);
    }

    if ((rendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0)
    {
        Log(objectName, "acceleration is not supported.", true, true);
        exit(1);
    }

    if (rm->GetAttribute(RESTYPE_SETTINGS, "Settings", "Video", "vSync") == "1"
            && rendererInfo.flags & SDL_RENDERER_PRESENTVSYNC == 0)
    {
        Log(objectName, "v-sync is not supported.", true, true);
        exit(1);
    }

    if ((rendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0)
    {
        Log(objectName, "render targets are not supported.", true, true);
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, 1920, 1080);

    // TODO: Create seperate function to change and draw background color
    SDL_SetRenderDrawColor(renderer, 16, 16, 96, 255);
    SDL_RenderClear(renderer);
}

void GraphicsHandler::Render()
{
    SDL_RenderClear(renderer);

    for (std::vector<TextureGroup>::iterator gi = textureGroups.begin(); gi != textureGroups.end(); ++gi)
    {
        // FIXME: buffering does not work - the concept might be wrong
        unsigned char groupIndex = std::distance(textureGroups.begin(), gi);

        // Buffering texture groups
//         if (SDL_SetRenderTarget(renderer, bufferedTextures.at(groupIndex)) < 0)
//         {
//             Log(objectName, gi->groupName + " setting rendering target failed: " + SDL_GetError(), true, true);
//             exit(2);
//         }
        PreRender(gi);

//         bufferedTextures.at(groupIndex) = SDL_GetRenderTarget(renderer);
//         if (bufferedTextures.at(groupIndex) == nullptr)
//         {
//             Log(objectName, gi->groupName + " getting rendering target failed: " + SDL_GetError(), true, true);
//             exit(2);
//         }
    }

    // Apply rendering to display
    SDL_RenderPresent(renderer);
}

void GraphicsHandler::CreateGroup(std::string groupName, unsigned char zIndex)
{
    // Check if texture group exists
    if (GetGroup(groupName) != textureGroups.end())
    {
//         Log(objectName, groupName + " creating failed: texture group already exists.", true, true);
        return;
    }

    // Find z-index to insert the new texture group to
    std::vector<TextureGroup>::iterator gi;
    for (gi = textureGroups.begin(); gi != textureGroups.end(); ++gi)
    {
        if (gi->zIndex > zIndex)
        {
            break;
        }
    }

    // Create new texture group
    textureGroups.emplace(gi, (TextureGroup)
    {
        groupName, false, zIndex
    });
}

void GraphicsHandler::DestroyGroup(std::string groupName)
{
    // Check if texture group exists
    std::vector<TextureGroup>::iterator gi = GetGroup(groupName);
    if (gi == textureGroups.end())
    {
        Log(objectName, groupName + " destroying failed: texture group doesn't exist.", true, true);
        return;
    }

    // Destroy texture group
    textureGroups.erase(gi);
}

Texture* GraphicsHandler::GetTexture(std::string groupName, std::string textureName)
{
    // Check if texture group exists
    std::vector<TextureGroup>::iterator gi = GetGroup(groupName);
    if (gi == textureGroups.cend())
    {
        return nullptr;
    }

    // Check if texture exists
    std::vector<Texture>::iterator ti = GetTextureIterator(groupName, textureName);
    if (ti == gi->textures.cend())
    {
        Log(objectName, groupName + ": getting failed: texture " + textureName + " doesn't exist.", true, true);
        return nullptr;
    }

    return &(*ti);
}

bool GraphicsHandler::AddTexture(std::string groupName,
                                 std::string textureName,
                                 SDL_Texture* texture,
                                 bool hidden,
                                 unsigned char zIndex,
                                 unsigned short int x,
                                 unsigned short int y,
                                 bool autoRemove)
{
    return AddTexture(groupName, textureName, (Texture)
    {
        textureName, texture, true, hidden, (Position)
        {
            zIndex, x, y
        }, false, autoRemove
    });
}

bool GraphicsHandler::AddTexture(std::string groupName, std::string textureName, Texture texture)
{
    // Check if texture group exists
    std::vector<TextureGroup>::iterator gi = GetGroup(groupName);
    if (gi == textureGroups.cend())
    {
        return false;
    }

    // Check if texture exists
    std::vector<Texture>::iterator ti = GetTextureIterator(groupName, textureName);
    if (ti != gi->textures.cend())
    {
//         Log(objectName, groupName + ": " + textureName + " already exists.", true, true);
        RemoveTexture(gi, ti);
    }

    // Find z-index to insert the new texture to
    for (ti = gi->textures.begin(); ti != gi->textures.end(); ++ti)
    {
        if ((*ti).position.zIndex > texture.position.zIndex)
        {
            break;
        }
    }

    // Add new texture
    gi->textures.emplace(ti, texture);
    if (!texture.autoRemove)
    {
        Log(objectName, groupName + ": " + textureName + " was successfully added.", true, true);
    }

    return true;
}

void GraphicsHandler::RemoveTexture(std::string groupName, std::string textureName)
{
    std::vector<TextureGroup>::iterator gi = GetGroup(groupName);
    std::vector<Texture>::iterator ti = GetTextureIterator(groupName, textureName);

    RemoveTexture(gi, ti);
}

void GraphicsHandler::LockTexture(std::string groupName, std::string resourceName, bool lock)
{
    // Check if texture exists
    std::vector<Texture>::iterator ti = GetTextureIterator(groupName, resourceName);
    if (ti == GetGroup(groupName)->textures.end())
    {
        Log(objectName, groupName + ": " + resourceName + " locking failed: texture not found.", true, true);
        return;
    }

    ti->locked = lock;
}

void GraphicsHandler::DrawSprite(std::string groupName,
                                 std::string textureName,
                                 std::string resourceName,
                                 unsigned short int positionX,
                                 unsigned short int positionY,
                                 unsigned char zIndex,
                                 AlignmentType horizontalAlignment,
                                 AlignmentType verticalAlignment,
                                 bool autoRemove)
{
    // Calculate X coordinate of position
    if (horizontalAlignment == ALIGN_NONE)
    {
        // Get X coordinate of origin from resource
        std::string value = rm->GetAttribute(RESTYPE_IMAGE, resourceName, "Image", "originX");
        if (value == "")
        {
            return;
        }

        positionX = positionX - std::stoi(value.c_str());
    }

    // Calculate Y coordinate of position
    if (verticalAlignment == ALIGN_NONE)
    {
        // Get origin coordinates from resource
        std::string value = rm->GetAttribute(RESTYPE_IMAGE, resourceName, "Image", "originY");
        if (value == "")
        {
            return;
        }

        positionY = positionY - std::stoi(value.c_str());
    }

    // Get image surface
    SDL_Surface *surface = rm->GetImage(resourceName);
    if (!surface)
    {
        return;
    }

    PrepareTexture(groupName, textureName, surface, positionX, positionY, zIndex, ALIGN_NONE, ALIGN_NONE, autoRemove);
}

void GraphicsHandler::DrawText(std::string groupName,
                               std::string text,
                               std::string fontName,
                               SDL_Color color,
                               unsigned short int positionX,
                               unsigned short int positionY,
                               unsigned char zIndex,
                               AlignmentType horizontalAlignment,
                               AlignmentType verticalAlignment,
                               bool autoRemove)
{
    // Get font resource
    TTF_Font* pFont = rm->GetFont(fontName);
    if (!pFont)
    {
        return;
    }

    // Create text surface
    SDL_Surface *surface = TTF_RenderText_Blended(pFont, text.c_str(), color);
    if (!surface)
    {
        Log(objectName, DRAW_TEXT_RES_PREFIX + text + ": cannot create surface: " + SDL_GetError(), true, true);
        return;
    }

    PrepareTexture(groupName, DRAW_TEXT_RES_PREFIX + text, surface, positionX, positionY, zIndex, horizontalAlignment,
                   verticalAlignment, autoRemove);
    SDL_FreeSurface(surface);
}

std::vector<TextureGroup>::iterator GraphicsHandler::GetGroup(std::string groupName)
{
    std::vector<TextureGroup>::iterator gi;
    for (gi = textureGroups.begin(); gi != textureGroups.end(); ++gi)
    {
        if (gi->groupName == groupName)
        {
            break;
        }
    }

    return gi;
}

std::vector<Texture>::iterator GraphicsHandler::GetTextureIterator(std::string groupName, std::string textureName)
{
    std::vector<Texture>::iterator ti;

    // Check if texture group exists
    std::vector<TextureGroup>::iterator gi = GetGroup(groupName);
    if (gi == textureGroups.cend())
    {
        Log(objectName, textureName + " getting failed: texture group " + groupName + " doesn't exist.", true, true);
        return ti;
    }

    // Check if texture exists
    for (ti = gi->textures.begin(); ti != gi->textures.end(); ++ti)
    {
        if (ti->textureName == textureName)
        {
            break;
        }
    }

    return ti;
}

void GraphicsHandler::PrepareTexture(std::string groupName,
                                     std::string textureName,
                                     SDL_Surface* surface,
                                     unsigned short int positionX,
                                     unsigned short int positionY,
                                     unsigned char zIndex,
                                     AlignmentType horizontalAlignment,
                                     AlignmentType verticalAlignment,
                                     bool autoRemove)
{
    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        Log(objectName, textureName + ": " + SDL_GetError(), true, true);
        return;
    }

    // Calculate rendering position coordinates
    int width, height;
    if (SDL_QueryTexture(texture, NULL, NULL, &width, &height) < 0)
    {
        Log(objectName, textureName + ": " + SDL_GetError(), true, true);
        return;
    }

    // Calculate X coordinate of the position
    switch (horizontalAlignment)
    {
    case ALIGN_CENTER:
        positionX = positionX - width / 2;
        break;
    case ALIGN_RIGHT:
        positionX = positionX - width;
        break;
    default:
        positionX = positionX;
        break;
    }

    // Calculate Y coordinate of the position
    switch (verticalAlignment)
    {
    case ALIGN_CENTER:
        positionY = positionY - height / 2;
        break;
    case ALIGN_BOTTOM:
        positionY = positionY - height;
        break;
    default:
        positionY = positionY;
        break;
    }

    AddTexture(groupName, textureName, texture, false, ZINDEX_LAST, positionX, positionY, autoRemove);
}

void GraphicsHandler::RemoveTexture(std::vector<TextureGroup>::iterator gi, std::vector<Texture>::iterator ti)
{
    // Check if texture group exists
    if (gi == textureGroups.end())
    {
        Log(objectName, "removing texture failed: texture group doesn't exist.", true, true);
        return;
    }

    // Check if texture exists
    if (ti == gi->textures.end())
    {
        Log(objectName, gi->groupName + ": removing texture failed: texture doesn't exist.", true, true);
        return;
    }

    std::string textureName = ti->textureName;
    if (!(ti->autoRemove))
    {
        Log(objectName, gi->groupName + ": " + textureName + " was successfully removed.", true, true);
    }

    SDL_DestroyTexture(ti->texture);
    gi->textures.erase(ti);
    gi->changed = true;

//     Log(objectName, gi->groupName + ": " + textureName + " was successfully removed.", true, true);
}

void GraphicsHandler::PreRender(std::vector<TextureGroup>::iterator gi)
{
    // Idea is to render group on top of the previous one.
    // TODO: probably wrong, should load previous group buffer

    // Check if any of the textures has changed
    std::vector<Texture>::iterator ti;
//     for (ti = gi->textures.begin(); ti != gi->textures.end(); ++ti)
//     {
//         if (ti->changed)
//         {
//             break;
//         }
//     }

    // Return if nothing changed
//     if (ti == gi->textures.end())
//     {
//         return;
//     }

    // Render textures
    for (ti = gi->textures.begin(); ti != gi->textures.end(); ++ti)
    {
        if (ti->hidden)
        {
            continue;
        }

        ApplyTexture(ti->texture, ti->position.x, ti->position.y);
        ti->changed = false;

        // Remove textures if not locked and autoremovable
        if (ti->autoRemove && !ti->locked)
        {
            RemoveTexture(gi, ti);
            --ti;
        }
    }
}

void GraphicsHandler::ApplyTexture(SDL_Texture* texture, unsigned short int positionX, unsigned short int positionY)
{
    if (!texture)
    {
        Log(objectName, SDL_GetError(), true, true);
        return;
    }

    // Create draw area
    SDL_Rect draw;
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    draw.x = positionX;
    draw.y = positionY;
    draw.w = width;
    draw.h = height;

    // Apply texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &draw);
}
