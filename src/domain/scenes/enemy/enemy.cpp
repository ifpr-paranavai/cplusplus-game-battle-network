#include "enemy.h"

namespace Game
{
    Enemy::Enemy() : Character(50, 50, "#FF0000")
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
        this->life = 100;
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
        float newRowIndex = this->tilePosition.y;
        float newColumnIndex = this->tilePosition.x;

        switch (direction)
        {
        case Direction::UP:
            newRowIndex--;
            break;
        case Direction::DOWN:
            newRowIndex++;
            break;
        case Direction::LEFT:
            newColumnIndex--;
            break;
        case Direction::RIGHT:
            newColumnIndex++;
            break;
        default:
            throw std::runtime_error("Invalid direction");
        }

        if (checkIsWithinTileLimits(newRowIndex, newColumnIndex))
        {
            this->setTilePosition({newColumnIndex, newRowIndex});
            return true;
        }
        return false;
    }

    bool Enemy::checkIsWithinTileLimits(int rowIndex, int columnIndex)
    {
        return rowIndex >= this->initialTileRowLimit &&
               rowIndex <= this->finalTileRowLimit &&
               columnIndex >= this->initialTileColumnLimit &&
               columnIndex <= this->finalTileColumnLimit;
    }

    void Enemy::update()
    {
        this->handleMovement();
        Character::update();
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