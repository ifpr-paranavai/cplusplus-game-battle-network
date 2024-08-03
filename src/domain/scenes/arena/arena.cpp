#include "arena.h"
#include <SDL2/SDL.h>

namespace Game
{
    Arena::Arena() : tileMap(new TileMap())
    {
        this->tileMap->init();
        this->configureBackground();
        this->createEnemies();
    }

    void Arena::configureBackground()
    {
        VisualElement background, clouds;
        background.setSpritePath("assets/sprites/background/bg.png");
        background.setConfig(
            this->backgroundColorHex,
            Vector(0, 0),
            Config::WINDOW_WIDTH,
            Config::WINDOW_HEIGHT);
        clouds.setSpritePath("assets/sprites/background/clouds.png");
        clouds.setConfig(
            this->backgroundColorHex,
            Vector(0, 0),
            Config::WINDOW_WIDTH,
            Config::WINDOW_HEIGHT);
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

    void Arena::renderBackground()
    {
        for (VisualElement bgSprite : this->backgroundSprites)
        {
            bgSprite.renderSprite();
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

        for (auto &projectile : Global::attacksService->getDyanmicAttacks())
        {
            projectile->render();
        }

        for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
        {
            tileBasedAttack->render();
        }
    }

    void Arena::render()
    {
        std::cout << "Arena::render() - " << SDL_GetTicks() << std::endl;
        for (Character *character : this->characters)
        {
            character->update();
        }
        std::cout << "character->update() - " << SDL_GetTicks() << std::endl;

        this->updateAttacks();
        std::cout << "updateAttacks() - " << SDL_GetTicks() << std::endl;

        this->renderBackground();
        std::cout << "renderBackground() - " << SDL_GetTicks() << std::endl;
        this->tileMap->render();
        std::cout << "tileMap->render() - " << SDL_GetTicks() << std::endl;
        this->renderPlayerLife();
        std::cout << "renderPlayerLife() - " << SDL_GetTicks() << std::endl;

        for (Character *character : this->characters)
        {
            character->render();
        }

        std::cout << "character->render() - " << SDL_GetTicks() << std::endl;

        this->renderAttacks();

        std::cout << "renderAttacks - " << SDL_GetTicks() << std::endl;

        Global::attacksService->removeExpiredAttacks();

        std::cout << "attacksService->removeExpiredAttacks() - " << SDL_GetTicks() << std::endl;
    }
}
