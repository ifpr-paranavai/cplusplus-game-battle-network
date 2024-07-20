#pragma once
#include <list>
#include <memory>
#include "../../scenes/projectile/projectile.h"

namespace Game
{
    class ProjectilesService
    {
        std::list<std::unique_ptr<Projectile>> projectiles;

    public:
        ProjectilesService();
        void addProjectile(std::unique_ptr<Projectile> projectile);
        void removeExpiredProjectiles();
        std::list<std::unique_ptr<Projectile>> &getProjectiles();
    };
}