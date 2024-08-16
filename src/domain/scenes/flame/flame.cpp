#include "flame.h"

namespace Game
{
    Flame::Flame(Vector tilePosition) : TileBasedBody(60, 80)
    {
        this->setTilePosition(tilePosition);
        Global::animationService->addAnimatedSprite(&this->animatedSprite);
        Global::adaptersInstance.audioManager->playWavSoundEffect(this->flameSFX);
    }
}