#include "fireman.h"

namespace Game
{
    FiremanEnemy::FiremanEnemy() : Enemy()
    {
        this->attackTime = 3;
        this->life = 300;
    }

    void FiremanEnemy::attack()
    {
        this->flamethrowerAttack();

        // const int randomAttackIndex = std::rand() % 2;
        // const Attacks choicedAttack = static_cast<Attacks>(randomAttackIndex);
        // switch (choicedAttack)
        // {
        // case Attacks::FLAMETHROWER:
        //     this->flamethrowerAttack();
        //     break;
        // case Attacks::BOMB:
        //     this->bombAttack();
        //     break;
        // default:
        //     throw std::runtime_error("Invalid attack");
        // }
    }

    void FiremanEnemy::flamethrowerAttack()
    {
        this->attackDelayTime = 3;

        const float yTileDecision = std::rand() % 3;
        this->setTilePosition({this->tileXLimit[0], yTileDecision});
        Global::attacksService->addTileBasedAttack(std::make_unique<Flamethrower>(this->tilePosition));

        std::cout << "Fireman: flamethrower attack" << std::endl;
    }

    void FiremanEnemy::bombAttack()
    {
        std::cout << "Fireman: bomb attack" << std::endl;
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
}