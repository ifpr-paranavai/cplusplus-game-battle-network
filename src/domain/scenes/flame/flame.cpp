#include "flame.h"

namespace Game
{
    Flame::Flame(Vector tilePosition) : TileBasedBody(60, 80), animatedSprite({0.2f,
                                                                               {
                                                                                   "assets/sprites/attacks/fire/0.png",
                                                                                   "assets/sprites/attacks/fire/1.png",
                                                                                   "assets/sprites/attacks/fire/2.png",
                                                                                   "assets/sprites/attacks/fire/3.png",
                                                                                   "assets/sprites/attacks/fire/4.png",
                                                                                   "assets/sprites/attacks/fire/5.png",
                                                                                   "assets/sprites/attacks/fire/6.png",
                                                                                   "assets/sprites/attacks/fire/7.png",
                                                                               },
                                                                               this->width,
                                                                               this->height,
                                                                               false,
                                                                               Vector(0, 0)})
    {
        this->setTilePosition(tilePosition);
        Global::animationService->addAnimatedSprite(&this->animatedSprite);
    }
}