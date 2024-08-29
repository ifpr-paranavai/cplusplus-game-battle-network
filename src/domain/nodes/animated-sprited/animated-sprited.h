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
    Subject<int> onAnimationEnd;
    std::vector<Sprite> sprites;
    size_t currentSpriteIndex = 0;
    float spriteDisplayTime;
    float elapsedTime = 0;

  public:
    AnimatedSprite(const AnimatedSpriteConfig &config);
    void update();
    void renderSprite(const Vector elementPosition) const;

    void subscribeToAnimationEnd(Observer<int> *observer)
    {
      this->onAnimationEnd.subscribe(observer);
    }
  };
}