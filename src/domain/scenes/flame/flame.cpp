#include "flame.h"

namespace Game
{
    Flame::Flame(Vector tilePosition) : TileBasedBody(60, 80), sprite({this->width,
                                                                       this->height,
                                                                       "assets/sprites/attacks/fire/0.png",
                                                                       false},
                                                                      Vector(0, 0))
    {
        this->setTilePosition(tilePosition);
    }
}