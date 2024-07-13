#include "renderer.h"

namespace Game
{
    SDLRendererAdapter::SDLRendererAdapter(
        SDLWindowManagerAdapter *_sdlWindowManagerAdapter) : sdlWindowManagerAdapter(_sdlWindowManagerAdapter)
    {
        this->sdlRenderer = nullptr;
        if (TTF_Init() == -1)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init failed: %s", TTF_GetError());
            throw std::runtime_error(TTF_GetError());
        }

        this->font = TTF_OpenFont("assets/fonts/Mega-Man-Battle-Network.ttf", 20);
        if (!font)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont failed: %s", TTF_GetError());
            throw std::runtime_error(TTF_GetError());
        }
    }

    SDL_Renderer *SDLRendererAdapter::getRenderer()
    {
        if (this->sdlRenderer == nullptr)
        {
            SDL_Window *window = this->sdlWindowManagerAdapter->getWindow();
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

    unsigned int SDLRendererAdapter::getHexColorValue(std::string_view hexColor)
    {
        std::string hex = std::string(hexColor);
        if (!hex.empty() && hex[0] == '#')
        {
            hex = hex.substr(1);
        }

        // Converte o valor hexadecimal para um valor inteiro
        std::stringstream ss;
        ss << std::hex << hex;
        unsigned int hexValue;
        ss >> hexValue;
        return hexValue;
    }

    void SDLRendererAdapter::renderElement(const RenderDataDTO &renderDataDTO)
    {
        unsigned int color = this->getHexColorValue(renderDataDTO.hexColor);
        Uint8 r = (color >> 16) & 0xFF;
        Uint8 g = (color >> 8) & 0xFF;
        Uint8 b = color & 0xFF;

        // Renderizar a borda
        SDL_Rect borderRect = {
            renderDataDTO.positionX - 2,
            renderDataDTO.positionY - 2,
            renderDataDTO.width + 2 * 2,
            renderDataDTO.height + 2 * 2};
        SDL_SetRenderDrawColor(this->getRenderer(), 50, 50, 50, 255); // Cor preta para a borda
        SDL_RenderFillRect(this->getRenderer(), &borderRect);

        // Renderizar o retângulo interno (conteúdo)
        SDL_Rect fillRect = {
            renderDataDTO.positionX,
            renderDataDTO.positionY,
            renderDataDTO.width,
            renderDataDTO.height};
        SDL_SetRenderDrawColor(this->getRenderer(), r, g, b, 255); // Cor interna do elemento
        SDL_RenderFillRect(this->getRenderer(), &fillRect);
    }

    void SDLRendererAdapter::updateScreen()
    {
        SDL_RenderPresent(this->getRenderer());
    }

    void SDLRendererAdapter::renderText(std::string_view text, int x, int y)
    {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Color borderColor = {0, 0, 0, 255};
        int borderSize = 2;

        // Create the text surface for the main text
        SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, text.data(), textColor);
        if (!textSurface)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid failed: %s", TTF_GetError());
            throw std::runtime_error(TTF_GetError());
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(this->getRenderer(), textSurface);
        if (!textTexture)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
            throw std::runtime_error(SDL_GetError());
        }

        SDL_Rect textRect;
        textRect.x = x;
        textRect.y = y;
        SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

        // Render the border by rendering the text in black in all surrounding positions
        for (int dx = -borderSize; dx <= borderSize; ++dx)
        {
            for (int dy = -borderSize; dy <= borderSize; ++dy)
            {
                // Skip the center position
                if (dx == 0 && dy == 0)
                    continue;

                SDL_Surface *borderSurface = TTF_RenderText_Solid(this->font, text.data(), borderColor);
                if (!borderSurface)
                {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid failed: %s", TTF_GetError());
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

        // Render the actual text on top
        SDL_RenderCopy(this->getRenderer(), textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    void SDLRendererAdapter::destroyRenderer()
    {
        this->sdlRenderer = nullptr;
        SDL_DestroyRenderer(this->getRenderer());
    }

}