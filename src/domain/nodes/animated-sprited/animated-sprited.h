#pragma once
#include <list>
#include <vector>
#include <string_view>
#include <optional>
#include "../sprite/sprite.h"
#include "../../../utils/global-adapters/global-adapters.h"

namespace Game
{
    struct AnimatedSpriteConfig
    {
        float spriteDisplayTime;
        std::list<std::string_view> spritesPath;
        float width;
        float height;
        bool flipHorizontal;
        Vector initialRelativePosition;
        std::optional<Color> spriteColorFilter;
    };

    class AnimatedSprite
    {
    private:
        std::vector<Sprite> sprites;
        size_t currentSpriteIndex = 0;
        float spriteDisplayTime;
        float elapsedTime = 0;

    public:
        AnimatedSprite(const AnimatedSpriteConfig &config);
        void update();
        void renderSprite(Vector elementPosition) const;
    };
}