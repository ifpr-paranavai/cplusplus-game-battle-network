#include "player-projectile.h"
#include "../../player/player.h"

namespace Game
{
    PlayerProjectile::PlayerProjectile(Vector initialPosition) : DynamicAttack(initialPosition)
    {
        this->velocity = {1000, 0};
        this->damage = 1;
        this->width = 30.5;
        this->height = 29.75;
        this->sprites.push_back(Sprite({this->width,
                                        this->height,
                                        "assets/sprites/attacks/projectile/0.png",
                                        false},
                                       Vector(0, 0)));
        Global::adaptersInstance.audioManager->playWavSoundEffect(this->projectileSFX);
    }

    void PlayerProjectile::onCollision(Element *other)
    {
        if (dynamic_cast<Player *>(other) || dynamic_cast<PlayerProjectile *>(other))
        {
            return;
        }

        this->deleted = true;
    }
}
