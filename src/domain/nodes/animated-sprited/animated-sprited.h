#pragma once
#include <list>
#include <vector>
#include <string_view>
#include <optional>
#include <functional>
#include "../sprite/sprite.h"
#include "../../../utils/global-adapters/global-adapters.h"

namespace Game
{
    struct AnimatedSpriteConfig
    {
        float spriteDisplayTime;
        std::string_view animationFolderPath;
        int animationFramesCount;
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
        std::list<std::function<void()>> callbacks;

    public:
        AnimatedSprite(const AnimatedSpriteConfig &config);
        void update();
        void renderSprite(Vector elementPosition) const;

        void addOnAnimationEndCallback(const std::function<void()> &callback)
        {
            this->callbacks.push_back(callback);
        }
    };
}