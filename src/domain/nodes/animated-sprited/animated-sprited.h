#pragma once
#include <list>
#include <vector>
#include <string_view>
#include <optional>
#include <functional>
#include "../sprite/sprite.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/subject/subject.h"
namespace Game
{
  struct AnimatedSpriteConfig
  {
    const float spriteDisplayTime;
    const std::string_view animationFolderPath;
    const int animationFramesCount;
    const int width;
    const int height;
    const bool flipHorizontal;
    const Vector initialRelativePosition;
    const std::optional<Color> spriteColorFilter;
  };

  class AnimatedSprite
  {
  private:
    const float spriteDisplayTime;

    Subject<int> onAnimationEnd;
    std::vector<Sprite> sprites;
    size_t currentSpriteIndex = 0;
    float elapsedTime = 0;

  public:
    AnimatedSprite(const AnimatedSpriteConfig &config);
    ~AnimatedSprite();
    inline void subscribeToAnimationEnd(Observer<int> *observer) { this->onAnimationEnd.subscribe(observer); }
    void update();
    void renderSprite(const Vector elementPosition) const;
  };
}