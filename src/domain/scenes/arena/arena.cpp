#include "arena.h"
#include <SDL2/SDL.h>

namespace Game
{
    Arena::Arena() : tileMap(new TileMap())
    {
        Global::adaptersInstance.audioManager->playMusic(this->music);
        this->tileMap->init();
        this->configureBackground();
        this->createEnemies();
    }

    void Arena::configureBackground()
    {
        Sprite background = Sprite({Config::WINDOW_WIDTH,
                                    Config::WINDOW_HEIGHT,
                                    "assets/sprites/background/bg.png",
                                    false,
                                    Vector(0, 0)});
        Sprite clouds = Sprite({Config::WINDOW_WIDTH,
                                Config::WINDOW_HEIGHT,
                                "assets/sprites/background/clouds.png",
                                false,
                                Vector(0, 0)});
        this->backgroundSprites.push_back(background);
        this->backgroundSprites.push_back(clouds);
    }

    void Arena::createEnemies()
    {
        auto *enemy = new FiremanEnemy();
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

    void Arena::updateAttacks()
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
    }

    void Arena::updateAnimations()
    {
        Global::animationService->updateAnimatedSprites();
    }

    void Arena::renderBackground()
    {
        for (const Sprite &bgSprite : this->backgroundSprites)
        {
            bgSprite.renderSprite(Vector(0, 0));
        }
    }

    void Arena::renderPlayerLife()
    {
        const std::string lifeStr = std::to_string(this->player->getLife());
        const int textHeight = Global::adaptersInstance.renderer->getTextHeight(lifeStr);
        const int textWidth = Global::adaptersInstance.renderer->getTextWidth(lifeStr);

        Global::adaptersInstance.renderer->renderElement({
            {10, 10},
            100,
            textHeight + 10,
            "#000000",
        });
        Global::adaptersInstance.renderer->renderText(lifeStr, {10 + 100 - textWidth, 15});
    }

    void Arena::renderAttacks()
    {

        for (const auto &projectile : Global::attacksService->getDyanmicAttacks())
        {
            projectile->render();
        }

        for (const auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
        {
            tileBasedAttack->render();
        }
    }

    void Arena::render()
    {
        this->updateAnimations();

        for (Character *character : this->characters)
        {
            character->update();
        }

        this->updateAttacks();

        this->renderBackground();
        this->tileMap->render();
        this->renderPlayerLife();

        for (Character *character : this->characters)
        {
            character->render();
        }

        this->renderAttacks();

        Global::attacksService->removeExpiredAttacks();
    }
}
