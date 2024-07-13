#include "arena.h"

namespace Game
{
    Arena::Arena(
        RendererPort *_renderer,
        TimeManagerPort *_timeManager) : renderer(_renderer),
                                         timeManager(_timeManager)
    {
        this->tileMap = new TileMap(this->renderer);
        this->tileMap->init();
        this->configureBackground();
        this->createEnemies();
    }

    void Arena::configureBackground()
    {
        this->background = new VisualElement(this->renderer);
        this->background->setConfig(
            this->backgroundColorHex,
            0,
            0,
            Config::WINDOW_WIDTH,
            Config::WINDOW_HEIGHT);
    }

    void Arena::createEnemies()
    {
        Enemy *enemy = new Enemy(this->renderer, this->timeManager);
        enemy->setTileCoords(4, 1);
        enemy->setTileLimits(
            6 - this->tileMap->getEnemyColumnTilesCount(),
            5,
            0,
            this->tileMap->getTilesRowsCount() - 1);
        this->enemies.push_back(enemy);
    }

    void Arena::setPlayer(Player *player)
    {
        this->player = player;
        this->player->setTileCoords(1, 1);
        this->player->setTileLimits(
            0,
            this->tileMap->getPlayerColumnTilesCount() - 1,
            0,
            this->tileMap->getTilesRowsCount() - 1);
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

        this->renderer->updateScreen();
        LogManager::log("Screen updated!");
    }
}
