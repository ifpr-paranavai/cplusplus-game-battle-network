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
        AnimatedSprite explosionAnimation = AnimatedSprite({0.1f,
                                                            "assets/sprites/attacks/explosion",
                                                            12,
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
        const float verticalDistance = 50.0f;
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