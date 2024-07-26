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
        FiremanEnemy *enemy = new FiremanEnemy();
        enemy->setTilePosition({4, 1});
        enemy->setTileXLimit({static_cast<float>(6 - this->tileMap->getEnemyColumnTilesCount()), 5});
        enemy->setTileYLimit({0, static_cast<float>(this->tileMap->getTilesRowsCount() - 1)});
        this->characters.push_back(enemy);
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
        LogManager::log("Rendering arena!");
        this->background.renderSprite();
        LogManager::log("Arena rendered!");
        this->tileMap->render();
        LogManager::log("TileMap rendered!");
        for (auto &projectile : Global::attacksService->getDyanmicAttacks())
        {
            projectile->move();
            LogManager::log("Projectile moved!");
            projectile->update();
            LogManager::log("Projectile updated!");
        }
        for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
        {
            tileBasedAttack->update();
            LogManager::log("TileBasedAttack updated!");
        }
        for (Character *character : this->characters)
        {
            character->update();
            LogManager::log("Character updated!");
            character->render();
            LogManager::log("Character rendered!");
            for (auto &projectile : Global::attacksService->getDyanmicAttacks())
            {
                projectile->checkCollision(character);
                LogManager::log("Projectile checked collision!");
                character->checkCollision(projectile.get());
                LogManager::log("Character checked collision!");
                projectile->render();
                LogManager::log("Projectile rendered!");
            }
            for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
            {
                tileBasedAttack->checkCollision(character);
                LogManager::log("TileBasedAttack checked collision!");
                character->checkCollision(tileBasedAttack.get());
                LogManager::log("Character checked collision!");
                tileBasedAttack->render();
                LogManager::log("TileBasedAttack rendered!");
            }
        }
        Global::attacksService->removeExpiredAttacks();
        Global::adaptersInstance.renderer->updateScreen();
        LogManager::log("Screen updated!");
    }
}
