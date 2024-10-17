#include "renderer.h"

namespace Game
{
  SDLRendererAdapter::SDLRendererAdapter()
  {
    IMG_Init(IMG_INIT_PNG);
  }

  SDLRendererAdapter::~SDLRendererAdapter()
  {
    this->destroyRenderer();
  }

  SDL_Renderer *SDLRendererAdapter::getRenderer()
  {
    if (this->sdlRenderer == nullptr)
    {
      SDLWindowManagerAdapter *windowManager = static_cast<Game::SDLWindowManagerAdapter *>(Global::adaptersInstance.windowManager);
      SDL_Window *window = windowManager->getWindow();

      this->sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      if (this->sdlRenderer == nullptr)
      {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL_Renderer: %s", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
      }
    }
    return this->sdlRenderer;
  }

  void SDLRendererAdapter::renderElement(const RenderElementData &renderDataDTO)
  {
    SDL_Rect fillRect = {
        static_cast<int>(std::round(renderDataDTO.position.x)),
        static_cast<int>(std::round(renderDataDTO.position.y)),
        renderDataDTO.width,
        renderDataDTO.height};
    SDL_SetRenderDrawColor(this->getRenderer(), renderDataDTO.color.r, renderDataDTO.color.g, renderDataDTO.color.b, 255);
    SDL_RenderFillRect(this->getRenderer(), &fillRect);
  }

  void SDLRendererAdapter::renderBorder(const RenderElementData &renderDataDTO)
  {
    SDL_SetRenderDrawColor(this->getRenderer(), renderDataDTO.color.r, renderDataDTO.color.g, renderDataDTO.color.b, 255);

    // Draw top border
    SDL_Rect topBorder = {
        static_cast<int>(std::round(renderDataDTO.position.x)) - 2,
        static_cast<int>(std::round(renderDataDTO.position.y)) - 2,
        renderDataDTO.width + 2 * 2,
        2};
    SDL_RenderFillRect(this->getRenderer(), &topBorder);

    // Draw bottom border
    SDL_Rect bottomBorder = {
        static_cast<int>(std::round(renderDataDTO.position.x)) - 2,
        static_cast<int>(std::round(renderDataDTO.position.y)) + renderDataDTO.height,
        renderDataDTO.width + 2 * 2,
        2};
    SDL_RenderFillRect(this->getRenderer(), &bottomBorder);

    // Draw left border
    SDL_Rect leftBorder = {
        static_cast<int>(std::round(renderDataDTO.position.x)) - 2,
        static_cast<int>(std::round(renderDataDTO.position.y)) - 2,
        2,
        renderDataDTO.height + 2 * 2};
    SDL_RenderFillRect(this->getRenderer(), &leftBorder);

    // Draw right border
    SDL_Rect rightBorder = {
        static_cast<int>(std::round(renderDataDTO.position.x)) + renderDataDTO.width,
        static_cast<int>(std::round(renderDataDTO.position.y)) - 2,
        2,
        renderDataDTO.height + 2 * 2};
    SDL_RenderFillRect(this->getRenderer(), &rightBorder);
  }

  void SDLRendererAdapter::updateScreen()
  {
    SDL_RenderPresent(this->getRenderer());
  }

  void SDLRendererAdapter::renderSprite(const SpriteTexture &spriteTexture, Vector position)
  {
    SDL_Texture *texture = std::any_cast<SDL_Texture *>(spriteTexture.data);
    SDL_Rect dstRect = {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(spriteTexture.width),
        static_cast<int>(spriteTexture.height)};
    SDL_RendererFlip flip;

    if (spriteTexture.flipVertically)
    {
      flip = SDL_FLIP_VERTICAL;
    }
    else if (spriteTexture.flipHorizontally)
    {
      flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
      flip = SDL_FLIP_NONE;
    }

    SDL_RenderCopyEx(this->getRenderer(), texture, nullptr, &dstRect, 0, nullptr, flip);
  }

  void SDLRendererAdapter::destroyRenderer()
  {
    if (sdlRenderer != nullptr)
    {
      SDL_DestroyRenderer(sdlRenderer);
      sdlRenderer = nullptr;
    }
  }

  SpriteTexture SDLRendererAdapter::getSpriteTexture(const RenderSpriteData &renderSpriteData)
  {
    SDL_Texture *texture = IMG_LoadTexture(this->getRenderer(), renderSpriteData.path.data());
    if (!texture)
    {
      throw std::runtime_error(IMG_GetError());
    }

    if (renderSpriteData.colorFilter)
    {
      const Color &colorFilter = renderSpriteData.colorFilter.value();
      SDL_SetTextureColorMod(texture, colorFilter.r, colorFilter.g, colorFilter.b);
      SDL_SetTextureAlphaMod(texture, colorFilter.a);
    }

    return SpriteTexture{std::make_any<SDL_Texture *>(texture), renderSpriteData.width, renderSpriteData.height, renderSpriteData.flipHorizontal};
  }

  void SDLRendererAdapter::destroySpriteTexture(const SpriteTexture &spriteTexture)
  {
    SDL_DestroyTexture(std::any_cast<SDL_Texture *>(spriteTexture.data));
  }

}