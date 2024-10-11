#include "text-renderer.h"

namespace Game
{
  SDLTextRendererAdapter::SDLTextRendererAdapter()
  {
    if (TTF_Init() == -1)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }

    this->font = TTF_OpenFont("assets/fonts/unifont.ttf", this->defaultFontSize);
    if (!font)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont ftextureCacheailed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }
  }

  SDLTextRendererAdapter::~SDLTextRendererAdapter()
  {
    if (this->font != nullptr)
    {
      TTF_CloseFont(this->font);
      this->font = nullptr;
    }
  }

  int SDLTextRendererAdapter::getTextHeight(std::string_view text)
  {
    int textWidth, textHeight;
    if (TTF_SizeText(this->font, text.data(), &textWidth, &textHeight) != 0)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_SizeText failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }
    return textHeight;
  }

  SDL_Renderer *SDLTextRendererAdapter::getRenderer()
  {
    SDLRendererAdapter *rendererAdapter = static_cast<Game::SDLRendererAdapter *>(Global::adaptersInstance.renderer);
    return rendererAdapter->getRenderer();
  }

  int SDLTextRendererAdapter::getTextWidth(std::string_view text)
  {
    int textWidth, textHeight;
    if (TTF_SizeText(this->font, text.data(), &textWidth, &textHeight) != 0)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_SizeText failed: %s", TTF_GetError());
      throw std::runtime_error(TTF_GetError());
    }
    return textWidth;
  }

  void SDLTextRendererAdapter::renderText(const RenderTextData &renderTextData)
  {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color borderColor = {0, 0, 0, 255};
    int borderSize = 2;

    if (renderTextData.color)
    {
      textColor = {renderTextData.color->r, renderTextData.color->g, renderTextData.color->b, 255};
    }

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

    for (int dx = -borderSize; dx <= borderSize; ++dx)
    {
      for (int dy = -borderSize; dy <= borderSize; ++dy)
      {
        if (dx == 0 && dy == 0)
          continue;

        SDL_Rect borderRect = textRect;
        borderRect.x += dx;
        borderRect.y += dy;
        SDL_RenderCopy(this->getRenderer(), borderTexture, NULL, &borderRect);
      }
    }

    SDL_RenderCopy(this->getRenderer(), textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(borderSurface);
    SDL_DestroyTexture(borderTexture);
  }

}