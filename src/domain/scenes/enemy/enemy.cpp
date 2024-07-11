#include "enemy.h"

namespace Game
{
    Enemy::Enemy(RendererPort *_renderer) : Character(_renderer, 50, 50, "#FF0000") {}

    void Enemy::update()
    {
        }
}