#pragma once
#include "../../../global/global-services/global-services.h"
#include "../../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../../nodes/tile-map/tile-map.h"
#include "../../../dto/sound-effect/sound-effect.h"

namespace Game
{
    class BombAttack : public DynamicAttack
    {
    private:
        AnimatedSprite explosionSprite = AnimatedSprite({0.1f,
                                                         {"assets/sprites/attacks/explosion/0.png",
                                                          "assets/sprites/attacks/explosion/1.png",
                                                          "assets/sprites/attacks/explosion/2.png",
                                                          "assets/sprites/attacks/explosion/3.png",
                                                          "assets/sprites/attacks/explosion/4.png",
                                                          "assets/sprites/attacks/explosion/5.png",
                                                          "assets/sprites/attacks/explosion/6.png",
                                                          "assets/sprites/attacks/explosion/7.png",
                                                          "assets/sprites/attacks/explosion/8.png",
                                                          "assets/sprites/attacks/explosion/9.png",
                                                          "assets/sprites/attacks/explosion/10.png",
                                                          "assets/sprites/attacks/explosion/11.png"},
                                                         64,
                                                         64,
                                                         false,
                                                         Vector(-16, -32)});
        AnimatedSprite *currentSprite = nullptr;
        const float maxHeight = 100;
        float timeToExplosion = 1;
        float timeToDelete = 1.2f;
        bool inTile = false;
        float xDistance;
        Vector initialPosition;
        Vector targetPosition;
        bool alreadyExploded = false;
        const SoundEffect grenadeThrowingSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/grenade-throwing.wav");
        const SoundEffect bombExplosionSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/explosion.wav");

        void calculatePositions(Vector elementTilePosition);
        void defineVelocity();
        void handleTargetReached();
        void checkExplosionTimer();
        void checkDeleteTimer();

    protected:
        void onCollision(Element *other) override;

    public:
        BombAttack(Vector elementPosition);

        void update() override;
        void render() override;
    };
}