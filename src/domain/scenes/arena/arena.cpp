#include "arena.h"

namespace Game
{
    Arena::Arena(RendererPort *_renderer) : renderer(_renderer)
    {
        this->tileMap = new TileMap(this->renderer);
        this->tileMap->init();
        this->configureBackground();
        this->createEnemies();
    }

    void Arena::configureBackground()
    {
        this->background = new VisualElement(this->renderer);
        this->background->setConfig(this->backgroundColorHex, 0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT);
    }

    void Arena::createEnemies()
    {
        Enemy *enemy = new Enemy(this->renderer);
        enemy->setTilePosition(4, 1);
        enemy->setTileLimits(this->tileMap->getEnemyColumnTilesCount() - 1, this->tileMap->getTilesRowsCount() - 1);
        this->enemies.push_back(enemy);
    }

    void Arena::setPlayer(Player *player)
    {
        this->player = player;
        this->player->setTilePosition(1, 1);
        this->player->setTileLimits(this->tileMap->getPlayerColumnTilesCount() - 1, this->tileMap->getTilesRowsCount() - 1);
    }

    void Arena::render()
    {
        this->player->update();
        this->background->renderSprite();
        this->tileMap->render();
        this->player->render();
        for (Enemy *enemy : this->enemies)
        {
            enemy->update();
            enemy->render();
        }
        this->renderer->updateScreen();
    }
}
