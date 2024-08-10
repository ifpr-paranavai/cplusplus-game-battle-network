#include "fireman.h"

namespace Game
{
    FiremanEnemy::FiremanEnemy() : Enemy(96, 96)
    {
        this->attackTime = 3;
        this->life = 300;
        this->updateCurrentAnimatedSprite(&this->idleSprite);
    }

    void FiremanEnemy::attack()
    {
        const int randomAttackIndex = std::rand() % 2;
        const Attacks choicedAttack = static_cast<Attacks>(randomAttackIndex);
        switch (choicedAttack)
        {
        case Attacks::FLAMETHROWER:
            this->flamethrowerAttack();
            break;
        case Attacks::BOMB:
            this->bombAttack();
            break;
        default:
            throw std::runtime_error("Invalid attack");
        }
    }

    void FiremanEnemy::flamethrowerAttack()
    {
        this->attackDelayTime = 3;

        const float yTileDecision = std::rand() % 3;
        this->setTilePosition({this->tileXLimit[0], yTileDecision});
        Global::attacksService->addTileBasedAttack(std::make_unique<FlamethrowerAttack>(this->tilePosition));
    }

    void FiremanEnemy::bombAttack()
    {
        this->attackDelayTime = 1;
        const float yTileDecision = std::rand() % 3;
        this->setTilePosition({this->tileXLimit[1], yTileDecision});
        Global::attacksService->addDynamicAttack(std::make_unique<BombAttack>(this->tilePosition));
    }

    void FiremanEnemy::update()
    {
        if (this->attackDelayTime > 0)
        {
            this->canMove = false;
            this->canAttack = false;
            this->attackDelayTime -= Global::adaptersInstance.timeManager->getDeltaTime();
        }
        else
        {
            this->canMove = true;
            this->canAttack = true;
        }
        Enemy::update();
    }

    void FiremanEnemy::onCollision(Element *other)
    {
        if (dynamic_cast<BombAttack *>(other))
        {
            return;
        }

        Enemy::onCollision(other);
    }

}