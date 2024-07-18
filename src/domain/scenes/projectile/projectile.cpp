#include "projectile.h"

namespace Game
{
    Projectile::Projectile(RendererPort *_renderer,
                           TimeManagerPort *_timeManager,
                           Vector initialPosition) : Element(_timeManager, 10, 10)
    {
        this->sprite = new VisualElement(_renderer);
        this->sprite->setConfig("#FFFF00", initialPosition, this->width, this->height);
        this->position = initialPosition;
    }

    void Projectile::update()
    {
        float deltaTime = this->timeManager->getDeltaTime();
        this->position += this->velocity * deltaTime;
        this->sprite->setPosition(this->position);
        if (this->position.x > Config::WINDOW_WIDTH)
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