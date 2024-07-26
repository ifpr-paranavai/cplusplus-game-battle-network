#include "projectiles-service.h"

namespace Game
{
    AttacksService::AttacksService()
    {
    }

    void AttacksService::removeExpiredAttacks()
    {
        for (auto it = this->dynamicAttacks.begin(); it != this->dynamicAttacks.end();)
        {
            if ((*it)->isDeleted())
            {
                it = this->dynamicAttacks.erase(it);
            }
            else
            {
                it++;
            }
        }

        for (auto it = this->tileBasedAttacks.begin(); it != this->tileBasedAttacks.end();)
        {
            if ((*it)->isDeleted())
            {
                it = this->tileBasedAttacks.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}