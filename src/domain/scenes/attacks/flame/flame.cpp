#include "flame.h"

namespace Game
{
  Flame::Flame(const Vector tilePosition)
  {
    this->width = 60;
    this->height = 80;
    this->setTilePosition(tilePosition);
    Global::animationService->addAnimatedSprite(&this->animatedSprite);
    Global::adaptersInstance.audioManager->playWavSoundEffect(this->flameSFX);
  }

  Flame::~Flame()
  {
    Global::adaptersInstance.audioManager->freeSoundEffect(this->flameSFX);
  }
}