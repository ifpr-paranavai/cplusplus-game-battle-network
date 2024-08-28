#include "player.h"

namespace Game
{
    Player::Player() : Character(96, 96)
    {
        this->queueAnimationChange(&this->idleSprite);
        this->collisionBoxes.emplace_back(this->position, this->width, this->height);
    }

    void Player::handleMovement()
    {
        const auto &keyboardManager = Global::adaptersInstance.keyboardManager;
        if (keyboardManager->isKeyPressed(KeyCode::ARROW_UP))
        {
            this->tryMoveUp();
        }
        else if (keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN))
        {
            this->tryMoveDown();
        }
        else if (keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT))
        {
            this->tryMoveLeft();
        }
        else if (keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT))
        {
            this->tryMoveRight();
        }
    }

    void Player::handleAttack()
    {
        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::X))
        {
            this->currentWeapon->attack(this->position, this->tilePosition);
        }
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

    void Player::handleChangeWeapon()
    {
        if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::C))
        {
            if (this->currentWeapon == &this->pistol)
            {
                this->currentWeapon = &this->sniper;
            }
            else if (this->currentWeapon == &this->sniper)
            {
                this->currentWeapon = &this->sword;
            }
            else
            {
                this->currentWeapon = &this->pistol;
            }
        }
    }

    void Player::update()
    {
        this->checkInvincibility();
        this->handleMovement();
        this->handleAttack();
        this->handleChangeWeapon();
        for (CollisionBox &collisionBox : this->collisionBoxes)
        {
            collisionBox.setPosition(this->position);
        }
        this->currentWeapon->update();
        Character::update();
    }

    void Player::onCollision(Element *other)
    {
        if (dynamic_cast<Projectile *>(other) || this->invencible || this->life <= 0)
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

    void Player::render()
    {
        Character::render();
        this->currentWeapon->render(this->position);
    }
}
