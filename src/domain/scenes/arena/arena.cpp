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
        this->background.setConfig(
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
        this->characters.push_back(std::move(enemy));
    }

    void Arena::setPlayer(Player *player)
    {
        this->player = player;
        this->player->setTilePosition({1, 1});
        this->player->setTileXLimit({0, static_cast<float>(this->tileMap->getPlayerColumnTilesCount() - 1)});
        this->player->setTileYLimit({0, static_cast<float>(this->tileMap->getTilesRowsCount() - 1)});
        this->characters.push_back(this->player);
    }

    void Arena::render()
    {

        this->background.renderSprite();
        this->tileMap->render();
        for (Character *character : this->characters)
        {
            character->update();
            for (Projectile *projectile : this->player->getProjectiles())
            {
                projectile->update();
                projectile->checkCollision(character);
                character->checkCollision(projectile);
                projectile->render();
            }
            character->render();
        }
        Global::adaptersInstance.renderer->updateScreen();
        LogManager::log("Screen updated!");
    }
}
