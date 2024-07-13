#include "enemy.h"

namespace Game
{
    Enemy::Enemy(
        RendererPort *_renderer,
        TimeManagerPort *_timeManager) : Character(_renderer,
                                                   _timeManager,
                                                   50,
                                                   50,
                                                   "#FF0000")
    {
        std::srand(static_cast<unsigned int>(std::time(0)));
    }

    void Enemy::handleMovement()
    {
        this->decisionTimer += this->timeManager->getDeltaTime();
        if (this->decisionTimer < this->decisionTime)
        {
            return;
        }
        this->decisionTimer = 0;

        bool isMoved = false;
        while (isMoved == false)
        {
            int randomDirection = std::rand() % 4;
            Direction moveDirection = static_cast<Direction>(randomDirection);
            switch (moveDirection)
            {
            case Direction::UP:
                if (this->tileRowIndex - 1 < this->initialTileRowLimit)
                {
                    break;
                }
                this->setTileRowIndex(this->tileRowIndex - 1);
                isMoved = true;
                break;
            case Direction::DOWN:
                if (this->tileRowIndex + 1 > this->finalTileRowLimit)
                {
                    break;
                }
                this->setTileRowIndex(this->tileRowIndex + 1);
                isMoved = true;
                break;
            case Direction::LEFT:
                if (this->tileColumnIndex - 1 < this->initialTileColumnLimit)
                {
                    break;
                }
                this->setTileColumnIndex(this->tileColumnIndex - 1);
                isMoved = true;
                break;
            case Direction::RIGHT:
                if (this->tileColumnIndex + 1 > this->finalTileColumnLimit)
                {
                    break;
                }
                this->setTileColumnIndex(this->tileColumnIndex + 1);
                isMoved = true;
                break;
            }
        }
    }

    void Enemy::update()
    {
        this->handleMovement();
        Character::update();
    }

    void Enemy::onCollision(Element *other)
    {
        this->life -= 1;
    }
}