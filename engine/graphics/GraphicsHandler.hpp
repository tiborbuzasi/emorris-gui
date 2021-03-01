/**
 * Graphics Handler for Interface Manager - Header File
 * eMorrisGUI
 *
 * @author Tibor Buzási <develop@tiborbuzasi.com>
 *
 * Copyright © 2020 Tibor Buzási. All rights reserved.
 * For licensing information see LICENSE in the project root folder.
 */

#ifndef GRAPHICS_HANDLER_H
#define GRAPHICS_HANDLER_H

#include "../ResourceManager.hpp"
#include "AlignmentType.hpp"
#include "Colors.hpp"
#include "TextureGroup.hpp"

class GraphicsHandler
{
private:
    /** Object name */
    const std::string objectName = "GraphicsHandler";

    /** Resource manager */
    ResourceManager* rm = nullptr;

    /** Renderer  for display */
    SDL_Renderer* renderer = nullptr;

    /** Vector of texture groups to render - rendering queue */
    std::vector<TextureGroup> textureGroups;

    /** Vector of buffered textures (from texture groups) */
    std::vector<SDL_Texture*> bufferedTextures;

    /**
     * Get texture group
     *
     * @param[in]   groupName           Name of the texture group
     *
     * @return      Iterator to the texture group
     */
    std::vector<TextureGroup>::iterator GetGroup(std::string groupName);

    /**
     * Get texture
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   textureName         Name of the texture
     *
     * @return      Iterator to the texture
     */
    std::vector<Texture>::iterator GetTextureIterator(std::string groupName, std::string textureName);

    /**
     * Prepare texture
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   textureName         Name of the texture
     * @param[in]   surface             Surface to convert
     * @param[in]   positionX           X coordinate of the position to draw to
     * @param[in]   positionY           Y coordinate of the position to draw to
     * @param[in]   zIndex              z-index of the sprite (default is on top)
     * @param[in]   horizontalAlignment Horizontal alignment of the image to the position (default is none)
     * @param[in]   verticalAlignment   Vertical alignment of the image to the position (default is none)
     * @param[in]   autoRemove          Remove automatically from queue after rendering
     */
    void PrepareTexture(std::string groupName,
                        std::string textureName,
                        SDL_Surface* surface,
                        unsigned short int positionX,
                        unsigned short int positionY,
                        unsigned char zIndex,
                        AlignmentType horizontalAlignment,
                        AlignmentType verticalAlignment,
                        bool autoRemove);

    /**
     * Remove texture from rendering queue
     *
     * @param[in]   gi                  Iterator to the texture group
     * @param[in]   ti                  Iterator to the texture
     */
    void RemoveTexture(std::vector<TextureGroup>::iterator gi, std::vector<Texture>::iterator ti);

    /**
     * Pre-render (buffer) texture group
     *
     * @param[in]   gi                  Iterator to the texture group
     */
    void PreRender(std::vector<TextureGroup>::iterator gi);

    /**
     * Apply texture to renderer
     *
     * @param[in]   texture             Texture to draw
     * @param[in]   positionX           X coordinate of the position to draw to
     * @param[in]   positionY           Y coordinate of the position to draw to
     */
    void ApplyTexture(SDL_Texture* texture, unsigned short int positionX, unsigned short int positionY);

public:
    /**
     * Initialize graphics handler
     *
     * @param[in]   resourceManager     Pointer to the resource manager
     * @param[in]   window              The window to render to
     */
    GraphicsHandler(ResourceManager* resourceManager, SDL_Window* window);

    /**
     * Render graphics onto the display
     */
    void Render();

    /**
     * Create texture group
     *
     * @param[in]   groupName           Name of the texture group to create
     * @param[in]   zIndex              Z-index of the texture group
     */
    void CreateGroup(std::string groupName, unsigned char zIndex);

    /**
     * Destroy texture group
     *
     * @param[in]   groupName           Name of the texture group to destroy
     */
    void DestroyGroup(std::string groupName);

    /**
     * Get texture
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   textureName         Name of the texture
     *
     * @return      Pointer to the texture
     */
    Texture* GetTexture(std::string groupName, std::string textureName);

    /**
     * Add texture to rendering queue
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   textureName         Name of the texture (for identification purposes)
     * @param[in]   texture             Pointer to the texture to add
     * @param[in]   hidden              The texture is hidden
     * @param[in]   zIndex              Z-index of the texture (inside the texture group)
     * @param[in]   x                   X coordinate of the rendering position
     * @param[in]   y                   Y coordinate of the rendering position
     * @param[in]   autoRemove          Remove automatically from queue after rendering
     */
    bool AddTexture(std::string groupName,
                    std::string textureName,
                    SDL_Texture* texture,
                    bool hidden,
                    unsigned char zIndex,
                    unsigned short int x,
                    unsigned short int y,
                    bool autoRemove);

    /**
     * Add texture to rendering queue
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   textureName         Name of the texture (for identification purposes)
     * @param[in]   texture             Texture structure to add
     *
     * @return      Successful addition of the texture to the queue
     */
    bool AddTexture(std::string groupName,
                    std::string textureName,
                    Texture texture);

    /**
     * Remove texture from rendering queue
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   textureName         Name of the texture (for identification purposes)
     */
    void RemoveTexture(std::string groupName, std::string textureName);

    /**
     * Lock/unlock sprite
     *
     * @param[in]   groupName           Name of the texture group
     * @param[in]   resourceName        Name of the image resource
     * @param[in]   lock                Lock resource
     */
    void LockTexture(std::string groupName, std::string resourceName, bool lock);

    /**
     * Draw sprite
     *
     * @param[in]   groupName           Name of the texture group to draw to
     * @param[in]   textureName         Name of the texture
     * @param[in]   resourceName        Name of the image resource
     * @param[in]   positionX           X coordinate of the position to draw to
     * @param[in]   positionY           Y coordinate of the position to draw to
     * @param[in]   zIndex              z-index of the sprite (default is on top)
     * @param[in]   horizontalAlignment Horizontal alignment of the image to the position (default is none)
     * @param[in]   verticalAlignment   Vertical alignment of the image to the position (default is none)
     * @param[in]   autoRemove          Remove automatically from queue after rendering
     */
    void DrawSprite(std::string groupName,
                    std::string textureName,
                    std::string resourceName,
                    unsigned short int positionX,
                    unsigned short int positionY,
                    unsigned char zIndex = ZINDEX_LAST,
                    AlignmentType horizontalAlignment = ALIGN_NONE,
                    AlignmentType verticalAlignment = ALIGN_NONE,
                    bool autoRemove = false);

    /**
     * Draw text
     *
     * @param[in]   groupName           Name of the texture group to draw to
     * @param[in]   text                Text to display
     * @param[in]   fontName            Font of the text
     * @param[in]   color               Color of the text
     * @param[in]   positionX           X coordinate of the position to draw to
     * @param[in]   positionY           Y coordinate of the position to draw to
     * @param[in]   zIndex              z-index of the sprite (default is on top)
     * @param[in]   horizontalAlignment Horizontal alignment of the image to the position (default is none)
     * @param[in]   verticalAlignment   Vertical alignment of the image to the position (default is none)
     * @param[in]   autoRemove          Remove automatically from queue after rendering
     */
    void DrawText(std::string groupName,
                  std::string text,
                  std::string fontName,
                  SDL_Color color,
                  unsigned short int positionX,
                  unsigned short int positionY,
                  unsigned char zIndex = ZINDEX_LAST,
                  AlignmentType horizontalAlignment = ALIGN_NONE,
                  AlignmentType verticalAlignment = ALIGN_NONE,
                  bool autoRemove = false);
};

/** Name of the texture group used by the draw functions */
const std::string DRAW_GROUP_NAME = "draw";

/** Prefix of the text resources */
const std::string DRAW_TEXT_RES_PREFIX = "text ";

#endif // GRAPHICS_HANDLER_H
