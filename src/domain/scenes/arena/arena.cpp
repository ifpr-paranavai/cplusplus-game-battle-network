#include "arena.h"

namespace Game
{
    Arena::Arena()
    {
        this->tileMap = new TileMap();
        this->tileMap->init();
        this->configureBackground();
        this->createEnemies();
    }

    void Arena::configureBackground()
    {
        this->background = new VisualElement();
        this->background->setConfig(
            this->backgroundColorHex,
            Vector(0, 0),
            Config::WINDOW_WIDTH,
            Config::WINDOW_HEIGHT);
    }

    void Arena::createEnemies()
    {
        Enemy *enemy = new Enemy();
        enemy->setTilePosition({4, 1});
        enemy->setTileXLimit({static_cast<float>(6 - this->tileMap->getEnemyColumnTilesCount()), 5});
        enemy->setTileYLimit({0, static_cast<float>(this->tileMap->getTilesRowsCount() - 1)});
        this->enemies.push_back(enemy);
    }

    void Arena::setPlayer(Player *player)
    {
        this->player = player;
        this->player->setTilePosition({1, 1});
        this->player->setTileXLimit({0, static_cast<float>(this->tileMap->getPlayerColumnTilesCount() - 1)});
        this->player->setTileYLimit({0, static_cast<float>(this->tileMap->getTilesRowsCount() - 1)});
    }

    void Arena::render()
    {
        LogManager::log("Rendering Arena...");
        this->player->update();
        LogManager::log("Player updated!");
        this->background->renderSprite();
        LogManager::log("Background rendered!");
        this->tileMap->render();
        LogManager::log("TileMap rendered!");
        this->player->render();
        LogManager::log("Player rendered!");
        for (Projectile *projectile : this->player->getProjectiles())
        {
            projectile->update();
            LogManager::log("Projectile updated!");
            for (Enemy *enemy : this->enemies)
            {
                projectile->checkCollision(enemy);
                LogManager::log("Projectile collided with enemy!");
            }
            projectile->render();
            LogManager::log("Projectile rendered!");
        }
        for (Enemy *enemy : this->enemies)
        {
            enemy->update();
            LogManager::log("Enemy updated!");
            for (Projectile *projectile : this->player->getProjectiles())
            {
                enemy->checkCollision(projectile);
                LogManager::log("Enemy collided with projectile!");
            }
            enemy->render();
            LogManager::log("Enemy rendered!");
        }

        Global::adaptersInstance.renderer->updateScreen();
        LogManager::log("Screen updated!");
    }
}
