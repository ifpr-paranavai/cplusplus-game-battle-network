#include "player.h"

namespace Game
{
    Player::Player() : Character(50, 70, "#00ADEF")
    {
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
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
            this->tryMoveUp();
            return;
        }

        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;
            this->tryMoveDown();
            return;
        }

        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;
            this->tryMoveLeft();
            return;
        }

        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT))
        {
            if (this->movementKeyAlreadyPressed)
            {
                return;
            }
            this->movementKeyAlreadyPressed = true;
            this->tryMoveRight();
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
        const Vector projectilePosition(
            this->position.x + this->width,
            this->position.y + this->height / 2);
        std::unique_ptr<PlayerProjectile> projectile = std::make_unique<PlayerProjectile>(projectilePosition);
        Global::attacksService->addDynamicAttack(std::move(projectile));
    }

    void Player::checkInvincibility()
    {
        if (!this->invencible)
        {
            return;
        }

        this->invencibleTimer -= Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->invencibleTimer <= 0)
        {
            this->invencible = false;
            this->invencibleTimer = this->invencibleTime;
        }
    }

    void Player::update()
    {
        this->checkInvincibility();
        this->handleMovement();
        this->handleAttack();
        for (CollisionBox &collisionBox : this->collisionBoxes)
        {
            collisionBox.setPosition(this->position);
        }
    }

    void Player::onCollision(Element *other)
    {
        if (dynamic_cast<PlayerProjectile *>(other) || this->invencible)
        {
            return;
        }

        if (this->life <= 0)
        {
            return;
        }

        if (auto attack = dynamic_cast<DynamicAttack *>(other))
        {
            this->life -= attack->getDamage();
            this->invencible = true;
        }
        else if (auto tileBasedAttack = dynamic_cast<TileBasedAttack *>(other))
        {
            this->life -= tileBasedAttack->getDamage();
            this->invencible = true;
        }
    }

}
