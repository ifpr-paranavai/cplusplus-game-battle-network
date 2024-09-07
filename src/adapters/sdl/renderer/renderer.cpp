#include "renderer.h"

namespace Game
{
  SDLRendererAdapter::SDLRendererAdapter()
  {
    this->sdlRenderer = nullptr;
    if (TTF_Init() == -1)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }

    this->font = TTF_OpenFont("assets/fonts/Mega-Man-Battle-Network.ttf", this->defaultFontSize);
    if (!font)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }

    IMG_Init(IMG_INIT_PNG);
  }

  SDL_Renderer *SDLRendererAdapter::getRenderer()
  {
    if (this->sdlRenderer == nullptr)
    {
      SDLWindowManagerAdapter *windowManager = static_cast<Game::SDLWindowManagerAdapter *>(Global::adaptersInstance.windowManager);
      SDL_Window *window = windowManager->getWindow();
      const char *windowTitle = SDL_GetWindowTitle(window);

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

  int SDLRendererAdapter::getTextHeight(std::string_view text)
  {
    int textWidth, textHeight;
    if (TTF_SizeText(this->font, text.data(), &textWidth, &textHeight) != 0)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_SizeText failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }
    return textHeight;
  }

  int SDLRendererAdapter::getTextWidth(std::string_view text)
  {
    int textWidth, textHeight;
    if (TTF_SizeText(this->font, text.data(), &textWidth, &textHeight) != 0)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_SizeText failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }
    return textWidth;
  }

  void SDLRendererAdapter::renderText(const RenderTextData &renderTextData)
  {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color borderColor = {0, 0, 0, 255};
    int borderSize = 2;

    if (renderTextData.fontSize)
    {
      TTF_SetFontSize(this->font, *renderTextData.fontSize);
    }
    else
    {
      TTF_SetFontSize(this->font, this->defaultFontSize);
    }

    SDL_Surface *textSurface = TTF_RenderUTF8_Blended_Wrapped(
        this->font,
        renderTextData.text.data(),
        textColor,
        renderTextData.maxWidth ? *renderTextData.maxWidth : 0);
    if (!textSurface)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderUTF8_Blended_Wrapped failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->getRenderer(), textSurface);
    if (!textTexture)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
      throw std::runtime_error(SDL_GetError());
    }

    SDL_Rect textRect;
    textRect.x = renderTextData.position.x;
    textRect.y = renderTextData.position.y;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

    for (int dx = -borderSize; dx <= borderSize; ++dx)
    {
      for (int dy = -borderSize; dy <= borderSize; ++dy)
      {
        if (dx == 0 && dy == 0)
          continue;

        SDL_Surface *borderSurface = TTF_RenderUTF8_Blended_Wrapped(
            this->font,
            renderTextData.text.data(),
            borderColor,
            renderTextData.maxWidth ? *renderTextData.maxWidth : 0);

        if (!borderSurface)
        {
          SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderUTF8_Blended_Wrapped failed: %s", TTF_GetError());
          throw std::runtime_error(TTF_GetError());
        }

        SDL_Texture *borderTexture = SDL_CreateTextureFromSurface(this->getRenderer(), borderSurface);
        if (!borderTexture)
        {
          SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
          throw std::runtime_error(SDL_GetError());
        }

        SDL_Rect borderRect = textRect;
        borderRect.x += dx;
        borderRect.y += dy;
        SDL_RenderCopy(this->getRenderer(), borderTexture, NULL, &borderRect);
        SDL_FreeSurface(borderSurface);
        SDL_DestroyTexture(borderTexture);
      }
    }

    SDL_RenderCopy(this->getRenderer(), textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
  }

  void SDLRendererAdapter::renderSprite(const SpriteTexture &spriteTexture, Vector position)
  {
    SDL_Texture *texture = std::any_cast<SDL_Texture *>(spriteTexture.data);
    SDL_Rect dstRect = {
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(spriteTexture.width),
        static_cast<int>(spriteTexture.height)};
    SDL_RendererFlip flip = spriteTexture.flipHorizontally ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(this->getRenderer(), texture, nullptr, &dstRect, 0, nullptr, flip);
  }

  void SDLRendererAdapter::destroyRenderer()
  {
    this->sdlRenderer = nullptr;
    SDL_DestroyRenderer(this->getRenderer());
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

}