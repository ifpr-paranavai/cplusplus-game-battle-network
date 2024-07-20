#include "enemy.h"

namespace Game
{
    Enemy::Enemy() : Character(50, 50, "#FF0000")
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        this->life = 100;
        this->collisionBoxes.push_back(CollisionBox(this->position, this->width, this->height));
    }

    void Enemy::handleMovement()
    {
        this->decisionTimer += Global::adaptersInstance.timeManager->getDeltaTime();
        if (this->decisionTimer < this->decisionTime)
        {
            return;
        }
        this->decisionTimer = 0;

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

    void Enemy::update()
    {
        this->handleMovement();
        for (CollisionBox &collisionBox : this->collisionBoxes)
        {
            collisionBox.setPosition(this->position);
        }
    }

    void Enemy::onCollision(Element *other)
    {
        if (this->dead)
        {
            return;
        }

        this->life -= 1;
        if (this->life <= 0)
        {
            this->dead = true;
        }
    }
}