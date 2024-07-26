#include "flamethrower.h"

namespace Game
{

    Flamethrower::Flamethrower(Vector elementPosition) : TileBasedAttack(50, 75)
    {
        this->damage = 10;
        this->tilePosition = elementPosition;
    }

    void Flamethrower::handleFlameIncrease()
    {
        this->increaseFlameTimer += Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->increaseFlameTimer < this->increaseFlameTime)
        {
            return;
        }
        this->increaseFlameTimer = 0;

        this->increaseFlame();
    }

    void Flamethrower::increaseFlame()
    {
        if (this->tilePosition.x - 1 < 0)
        {
            this->deleted = true;
            return;
        }

        this->setTilePosition({this->tilePosition.x - 1, this->tilePosition.y});
        VisualElement flame;
        flame.setConfig("#FFD700", this->position, this->width, this->height);
        this->flames.push_back(flame);
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, 10));
    }

    void Flamethrower::update()
    {
        this->handleFlameIncrease();
    }

    void Flamethrower::render()
    {
        for (VisualElement &flame : this->flames)
        {
            flame.renderSprite();
        }
    }

    void Flamethrower::onCollision(Element *other)
    {
    }

}