#include "player.h"

namespace Game
{
    Player::Player() : Character(50, 70, "#00ADEF")
    {
        LogManager::log("Creating collision box");
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
        LogManager::log("Collision added to list");
    }

    void Player::handleMovement()
    {
        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_UP))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tilePosition.y - 1 < this->initialTileRowLimit)
            {
                return;
            }
            this->setTilePosition({this->tilePosition.x, this->tilePosition.y - 1});
            return;
        }

        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tilePosition.y + 1 > this->finalTileRowLimit)
            {
                return;
            }
            this->setTilePosition({this->tilePosition.x, this->tilePosition.y + 1});
            return;
        }

        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tilePosition.x - 1 < this->initialTileColumnLimit)
            {
                return;
            }
            this->setTilePosition({this->tilePosition.x - 1, this->tilePosition.y});
            return;
        }

        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;

            if (this->tilePosition.x + 1 > this->finalTileColumnLimit)
            {
                return;
            }

            this->setTilePosition({this->tilePosition.x + 1, this->tilePosition.y});
            return;
        }

        this->movementKeyAlreadyPressed = false;
    }

    void Player::handleAttack()
    {
        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::X))
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
            Vector(this->position.x + this->width,
                   this->position.y + this->height / 2));
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
        for (CollisionBox &collisionBox : this->collisionBoxes)
        {
            collisionBox.setPosition(this->position);
        }
    }

    std::list<Projectile *> Player::getProjectiles()
    {
        return this->projectiles;
    }

    void Player::onCollision(Element *other)
    {
    }

}
