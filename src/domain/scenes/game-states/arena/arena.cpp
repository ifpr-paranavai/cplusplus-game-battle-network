#include "arena.h"
#include <SDL2/SDL.h>

namespace Game
{
  Arena::Arena()
  {
    Global::adaptersInstance.audioManager->playMusic(this->music);
    this->cardSelectorDelayBar.subscribeToOnCompleteLoad(&this->unblockOpenCardSelectorHandler);
    this->cardSelector.subscribeToOnSelectCard(&this->closeCardSelectorDelayHandler);
    this->tileMap.init();
    this->createEnemies();
    this->setPlayer(new Player());
  }

  Arena::~Arena()
  {
    for (Character *character : characters)
    {
      delete character;
    }
  }

  void Arena::createEnemies()
  {
    auto *enemy = new FiremanEnemy();
    enemy->setTilePosition({4, 1});
    enemy->setTileXLimit({static_cast<float>(6 - this->tileMap.getEnemyColumnTilesCount()), 5});
    enemy->setTileYLimit({0, static_cast<float>(this->tileMap.getTilesRowsCount() - 1)});
    enemy->subscribeToDeath(&this->victoryHandler);
    enemy->subscribeToDeath(new SaveScoreHandler());
    enemy->subscribeToOnCollide(&this->pointsIncrementHandler);
    this->characters.push_back(enemy);
  }

  void Arena::setPlayer(Player *player)
  {
    this->player = player;
    this->player->setTilePosition({1, 1});
    this->player->setTileXLimit({0, static_cast<float>(this->tileMap.getPlayerColumnTilesCount() - 1)});
    this->player->setTileYLimit({0, static_cast<float>(this->tileMap.getTilesRowsCount() - 1)});
    this->player->subscribeToDeath(&this->gameOverHandler);
    this->characters.push_back(this->player);
    this->cardSelector.subscribeToOnSelectCard(this->player->getSetSelectedCardHandler());
  }

  void Arena::updateAttacks()
  {
    for (auto &projectile : Global::attacksService->getDynamicAttacks())
    {
      projectile->move();
      projectile->update();
    }

    for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
    {
      tileBasedAttack->update();
    }

    for (auto &projectile : Global::attacksService->getDynamicAttacks())
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
    auto textRenderer = Global::adaptersInstance.textRenderer;
    const int textHeight = textRenderer->getTextHeight(lifeStr);
    const int textWidth = textRenderer->getTextWidth(lifeStr);

    Global::adaptersInstance.renderer->renderBorder({
        {10, 10},
        100,
        textHeight + 10.0f,
        Color{0, 0, 0, 255},
    });
    textRenderer->renderText({lifeStr, {10 + 100 - textWidth, 15}});
  }

  void Arena::renderPlayerPoints()
  {
    // const std::string pointsStr = std::to_string(this->playerPoints) + " PTS";
    // Global::adaptersInstance.renderer->renderText({pointsStr, {Config::WINDOW_WIDTH - textWidth - 10, 10}});
    const float elapsedTime = Global::adaptersInstance.timeManager->getElapsedTime();
    auto textRenderer = Global::adaptersInstance.textRenderer;
    const std::string elapsedTimeStr = std::to_string(int(elapsedTime / 60)) + " " + std::to_string(int(elapsedTime) % 60);
    const int textWidth = textRenderer->getTextWidth(elapsedTimeStr);
    textRenderer->renderText({elapsedTimeStr, {Config::WINDOW_WIDTH - textWidth - 10, 10}});
  }

  void Arena::renderAttacks()
  {

    for (const auto &projectile : Global::attacksService->getDynamicAttacks())
    {
      projectile->render();
    }

    for (const auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
    {
      tileBasedAttack->render();
    }
  }

  void Arena::renderRunningMode()
  {
    for (Character *character : this->characters)
    {
      character->update();
    }

    this->updateAttacks();
    this->updateAnimations();
    this->cardSelectorDelayBar.update();

    this->renderBackground();
    this->tileMap.render();
    this->renderPlayerLife();
    this->renderPlayerPoints();
    this->cardSelectorDelayBar.render();

    for (Character *character : this->characters)
    {
      character->render();
    }

    this->renderAttacks();
    Global::attacksService->removeExpiredAttacks();
  }

  void Arena::checkKeyboard()
  {
    if (
        this->arenaMode == ArenaMode::RUNNING &&
        this->canOpenCardSelector &&
        Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::Z))
    {
      this->arenaMode = ArenaMode::CARD_SELECTOR_OPENED;
    }
  }

  void Arena::render()
  {
    this->checkKeyboard();
    switch (this->arenaMode)
    {
    case ArenaMode::RUNNING:
      this->renderRunningMode();
      break;
    case ArenaMode::VICTORY:
      Global::adaptersInstance.textRenderer->renderText({"VICTORY", {100, 100}});
      break;
    case ArenaMode::GAME_OVER:
      Global::adaptersInstance.textRenderer->renderText({"GAME OVER", {100, 100}});
      break;
    case ArenaMode::CARD_SELECTOR_OPENED:
      this->cardSelector.update();
      this->cardSelector.render();
      break;
    }
  }
}
