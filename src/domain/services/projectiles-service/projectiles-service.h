#pragma once
#include <list>
#include <memory>
#include "../../nodes/dynamic-attack/dynamic-attack.h"
#include "../../nodes/tile-based-attack/tile-based-attack.h"

namespace Game
{
    class AttacksService
    {
        std::list<std::unique_ptr<DynamicAttack>> dynamicAttacks;
        std::list<std::unique_ptr<TileBasedAttack>> tileBasedAttacks;

    public:
        AttacksService();

        void removeExpiredAttacks();

        void addDynamicAttack(std::unique_ptr<DynamicAttack> projectile)
        {
            this->dynamicAttacks.push_back(std::move(projectile));
        }

        void addTileBasedAttack(std::unique_ptr<TileBasedAttack> tileBasedAttack)
        {
            this->tileBasedAttacks.push_back(std::move(tileBasedAttack));
        }

        auto &getDyanmicAttacks()
        {
            return this->dynamicAttacks;
        }

        auto &getTileBasedAttacks()
        {
            return this->tileBasedAttacks;
        }
    };
}