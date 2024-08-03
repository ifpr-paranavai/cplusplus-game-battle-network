#include "enemy.h"

namespace Game
{
    Enemy::Enemy(int width, int height) : Character(width, height, "#FF0000")
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
        this->sprite.setFlipSpriteHorizontally(true);
    }

    void Enemy::handleMovement()
    {
        if (!this->canMove)
        {
            this->movementDecisionTimer = 0;
            return;
        }

        this->movementDecisionTimer += Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->movementDecisionTimer < this->movementDecisionTime)
        {
            return;
        }
        this->movementDecisionTimer = 0;

        moveRandomlyWithinLimits();
    }

    void Enemy::moveRandomlyWithinLimits()
    {
        while (true)
        {
            const Direction moveDirection = getRandomDirection();
            if (tryMove(moveDirection))
            {
                break;
            }
        }
    }

    Direction Enemy::getRandomDirection()
    {
        int randomDirectionIndex = std::rand() % 4;
        return static_cast<Direction>(randomDirectionIndex);
    }

    bool Enemy::tryMove(Direction direction)
    {
        switch (direction)
        {
        case Direction::UP:
            return this->tryMoveUp();
        case Direction::DOWN:
            return this->tryMoveDown();
        case Direction::LEFT:
            return this->tryMoveLeft();
        case Direction::RIGHT:
            return this->tryMoveRight();
        default:
            throw std::runtime_error("Invalid direction");
        }
    }

    void Enemy::handleAttack()
    {
        if (!this->canAttack)
        {
            this->attackTimer = 0;
            return;
        }

        this->attackTimer += Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->attackTimer < this->attackTime)
        {
            return;
        }

        this->attackTimer = 0;
        this->attack();
    }

    void Enemy::update()
    {
        this->handleMovement();
        this->handleAttack();
        for (CollisionBox &collisionBox : this->collisionBoxes)
        {
            collisionBox.setPosition(this->position);
        }
    }

    void Enemy::onCollision(Element *other)
    {
        if (this->dead || dynamic_cast<EnemyProjectile *>(other))
        {
            return;
        }

        if (DynamicAttack *projectile = dynamic_cast<DynamicAttack *>(other))
        {
            this->life -= projectile->getDamage();
        }

        if (this->life <= 0)
        {
            this->dead = true;
        }
    }

    void Enemy::render()
    {
        Character::render();
        const Vector textPosition = {this->position.x, this->position.y + this->height + 5};
        Global::adaptersInstance.renderer->renderText(std::to_string(this->life), textPosition);
    }
}