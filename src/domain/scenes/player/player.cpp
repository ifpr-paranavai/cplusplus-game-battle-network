#include "player.h"

namespace Game
{
    Player::Player(
        RendererPort *_renderer,
        KeyboardManagerPort *_eventManager,
        TimeManagerPort *_timeManeger) : Character(_renderer,
                                                   _timeManeger,
                                                   50,
                                                   70,
                                                   "#00ADEF"),
                                         eventManager(_eventManager)
    {
    }

    void Player::handleMovement()
    {
        if (this->eventManager->isKeyPressed(KeyCode::ARROW_UP))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tileRowIndex - 1 < this->initialTileRowLimit)
            {
                return;
            }
            this->setTileRowIndex(this->tileRowIndex - 1);
            return;
        }

        if (this->eventManager->isKeyPressed(KeyCode::ARROW_DOWN))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tileRowIndex + 1 > this->finalTileRowLimit)
            {
                return;
            }
            this->setTileRowIndex(this->tileRowIndex + 1);
            return;
        }

        if (this->eventManager->isKeyPressed(KeyCode::ARROW_LEFT))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tileColumnIndex - 1 < this->initialTileColumnLimit)
            {
                return;
            }
            this->setTileColumnIndex(this->tileColumnIndex - 1);
            return;
        }

        if (this->eventManager->isKeyPressed(KeyCode::ARROW_RIGHT))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tileColumnIndex + 1 > this->finalTileColumnLimit)
            {
                return;
            }

            this->setTileColumnIndex(this->tileColumnIndex + 1);
            return;
        }

        this->movementKeyAlreadyPressed = false;
    }

    void Player::handleAttack()
    {
        if (this->eventManager->isKeyPressed(KeyCode::X))
        {
            if (this->attackKeyAlreadyPressed)
            {
                return;
            }

            this->attackKeyAlreadyPressed = true;
            this->attack();
            return;
        }

        this->attackKeyAlreadyPressed = false;
    }

    void Player::attack()
    {
        Projectile *projectile = new Projectile(
            this->renderer,
            this->timeManager,
            this->positionX + this->width,
            this->positionY + this->height / 2);
        this->projectiles.push_back(projectile);
    }

    void Player::checkProjectiles()
    {
        auto it = this->projectiles.begin();
        while (it != this->projectiles.end())
        {
            if ((*it)->isDeleted())
            {
                delete *it;
                it = this->projectiles.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    void Player::update()
    {
        this->checkProjectiles();
        this->handleMovement();
        this->handleAttack();
        Character::update();
    }

    std::list<Projectile *> Player::getProjectiles()
    {
        return this->projectiles;
    }

    void Player::onCollision(Element *other)
    {
    }

}
