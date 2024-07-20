#include "projectiles-service.h"

namespace Game
{
    ProjectilesService::ProjectilesService()
    {
    }

    void ProjectilesService::addProjectile(std::unique_ptr<Projectile> projectile)
    {
        this->projectiles.push_back(std::move(projectile));
    }

    std::list<std::unique_ptr<Projectile>> &ProjectilesService::getProjectiles()
    {
        return this->projectiles;
    }

    void ProjectilesService::removeExpiredProjectiles()
    {
        for (auto it = this->projectiles.begin(); it != this->projectiles.end();)
        {
            if ((*it)->isDeleted())
            {
                it = this->projectiles.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}