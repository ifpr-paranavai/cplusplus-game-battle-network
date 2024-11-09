#pragma once
#include <list>
#include <vector>
#include <string_view>
#include <optional>
#include <functional>
#include "../sprite/sprite.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../utils/subject/subject.h"
#include "../visual-entity/visual-entity.h"

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
    const Vector position;
    const std::optional<Color> spriteColorFilter;
  };

  class AnimatedSprite : public VisualEntity
  {
  private:
    const float spriteDisplayTime;

    bool flipVertically = false;
    bool flipHorizontally = false;
    float elapsedTime = 0;
    size_t currentSpriteIndex = 0;
    Subject<int> onAnimationEnd;
    std::vector<SpriteTexture> spriteTextures;

    void initSprites(const AnimatedSpriteConfig &config);

  public:
    AnimatedSprite(const AnimatedSpriteConfig &config);
    ~AnimatedSprite();
    void update() override;
    void render(const Vector &basePosition) const override;
    inline void subscribeToAnimationEnd(Observer<int> *observer) { this->onAnimationEnd.subscribe(observer); }
  };
}