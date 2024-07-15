#include "projectile.h"

namespace Game
{
    Projectile::Projectile(RendererPort *_renderer,
                           TimeManagerPort *_timeManager,
                           int initialX,
                           int initialY) : Element(_timeManager, 10, 10)
    {
        this->sprite = new VisualElement(_renderer);
        this->sprite->setConfig("#FFFF00", initialX, initialY, this->width, this->height);
        this->positionX = initialX;
        this->positionY = initialY;
    }

    void Projectile::update()
    {
        float deltaTime = this->timeManager->getDeltaTime();
        this->positionX = this->positionX + this->speedVel * deltaTime;
        this->sprite->setPosition(this->positionX, this->positionY);
        if (this->positionX > Config::WINDOW_WIDTH)
        {
            this->deleted = true;
        }
        Element::update();
    }

    void Projectile::render()
    {
        this->sprite->renderSprite();
    }

    void Projectile::onCollision(Element *other)
    {
        this->deleted = true;
    }

    bool Projectile::isDeleted()
    {
        return this->deleted;
    }
}