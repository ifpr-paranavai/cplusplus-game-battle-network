#include "flamethrower-attack.h"

namespace Game
{

    FlamethrowerAttack::FlamethrowerAttack(Vector elementPosition) : TileBasedAttack(60, 80)
    {
        this->damage = 10;
        this->tilePosition = elementPosition;
    }

    void FlamethrowerAttack::handleFlameIncrease()
    {
        this->increaseFlameTimer += Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->increaseFlameTimer < this->increaseFlameTime)
        {
            return;
        }
        this->increaseFlameTimer = 0;

        this->increaseFlame();
    }

    void FlamethrowerAttack::increaseFlame()
    {
        if (this->tilePosition.x - 1 < 0)
        {
            this->deleted = true;
            return;
        }

        this->setTilePosition({this->tilePosition.x - 1, this->tilePosition.y});
        Flame flame = Flame(this->tilePosition);
        this->flames.push_back(flame);
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, 10));
    }

    void FlamethrowerAttack::update()
    {
        this->handleFlameIncrease();
    }

    void FlamethrowerAttack::render()
    {
        for (Flame &flame : this->flames)
        {
            flame.renderSprite();
        }
    }

    void FlamethrowerAttack::onCollision(Element *other)
    {
    }

}