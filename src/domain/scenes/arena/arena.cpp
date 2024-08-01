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
        for (auto &projectile : Global::attacksService->getDyanmicAttacks())
        {
            projectile->move();
            projectile->update();
        }

        for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
        {
            tileBasedAttack->update();
        }

        for (Character *character : this->characters)
        {
            character->update();
        }

        for (auto &projectile : Global::attacksService->getDyanmicAttacks())
        {
            for (Character *character : this->characters)
            {
                projectile->checkCollision(character);
                character->checkCollision(projectile.get());
            }
        }

        for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
        {
            for (Character *character : this->characters)
            {
                tileBasedAttack->checkCollision(character);
                character->checkCollision(tileBasedAttack.get());
            }
        }

        this->background.renderSprite();
        this->tileMap->render();

        for (auto &projectile : Global::attacksService->getDyanmicAttacks())
        {
            projectile->render();
        }

        for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
        {
            tileBasedAttack->render();
        }

        for (Character *character : this->characters)
        {
            character->render();
        }

        Global::attacksService->removeExpiredAttacks();
    }

}
