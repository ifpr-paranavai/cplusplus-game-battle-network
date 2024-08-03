#include "bomb-attack.h"

namespace Game
{
    BombAttack::BombAttack(Vector elementTilePosition) : DynamicAttack(elementTilePosition)
    {
        this->width = 32;
        this->height = 32;
        this->movementTime = 1.0f;
        this->damage = 15;
        this->calculatePositions(elementTilePosition);
        this->defineVelocity();
        this->sprite.setSpritePath("assets/sprites/attacks/bomb/0.png");
        this->sprite.setConfig("#FFFF00", this->initialPosition, this->width, this->height);
    }

    void BombAttack::calculatePositions(Vector elementTilePosition)
    {
        const Vector tileTargetPosition = {elementTilePosition.x - 3, elementTilePosition.y};
        this->targetPosition = TileMap::getElementPositionInTile(tileTargetPosition, this->width, this->height);
        this->initialPosition = TileMap::getElementPositionInTile(elementTilePosition, this->width, this->height);
        this->targetPosition.y += this->height;
        this->initialPosition.y += this->height;
        this->position = this->initialPosition;
        Vector deltaPosition = this->initialPosition - this->targetPosition;
        this->xDistance = deltaPosition.x;
    }

    void BombAttack::defineVelocity()
    {
        const float verticalDistance = 50.0f;
        this->velocity.x = -this->xDistance / this->movementTime;
        this->downForce = 8 * verticalDistance / (this->movementTime * this->movementTime / 4);
        this->velocity.y = -this->downForce * this->movementTime / 2;
    }

    void BombAttack::handleTargetReached()
    {
        if (this->movementFinished)
        {
            this->velocity = {0, 0};
            this->inTile = true;
        }
    }

    void BombAttack::checkInTileTimer()
    {
        if (!this->inTile)
        {
            return;
        }

        this->inTileTimer -= Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->inTileTimer <= 0)
        {
            this->deleted = true;
        }
    }

    void BombAttack::update()
    {
        DynamicAttack::update();
        this->handleTargetReached();
        this->checkInTileTimer();
    }

    void BombAttack::onCollision(Element *other)
    {
    }
}
