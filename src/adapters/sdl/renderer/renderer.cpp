#include "renderer.h"

namespace Game
{
    SDLRendererAdapter::SDLRendererAdapter(
        SDLWindowManagerAdapter *_sdlWindowManagerAdapter) : sdlWindowManagerAdapter(_sdlWindowManagerAdapter)
    {
        this->font = TTF_OpenFont("../../../../assets/fonts/Mega-Man-Battle-Network.ttf", 24);
    }

    SDL_Renderer *SDLRendererAdapter::getRenderer()
    {
        if (this->sdlRenderer == NULL)
        {
            this->sdlRenderer = SDL_CreateRenderer(this->sdlWindowManagerAdapter->getWindow(), -1, SDL_RENDERER_ACCELERATED);
            if (this->sdlRenderer == NULL)
            {
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
}