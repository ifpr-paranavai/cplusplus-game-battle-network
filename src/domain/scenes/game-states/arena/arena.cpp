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

    Global::adaptersInstance.audioManager->freeMusic(this->music);
  }

  void Arena::createEnemies()
  {
    auto *enemy = new FiremanEnemy();
    enemy->setTilePosition({4, 1});
    enemy->setTileXLimit({static_cast<float>(6 - this->tileMap.getEnemyColumnTilesCount()), 5});
    enemy->setTileYLimit({0, static_cast<float>(this->tileMap.getTilesRowsCount() - 1)});
    enemy->subscribeToDeath(&this->victoryHandler);
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

  void Arena::renderPlayerLife() const
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

  void Arena::renderPlayedTime() const
  {
    const float playedTime = Global::adaptersInstance.timeManager->getElapsedTime() - this->arenaStartedAt;
    auto textRenderer = Global::adaptersInstance.textRenderer;
    const auto playedTimeStr = TimeUtil::formatElapsedTime(playedTime);
    const int textWidth = textRenderer->getTextWidth(playedTimeStr);
    textRenderer->renderText({playedTimeStr, {Config::WINDOW_WIDTH - textWidth - 10, 10}});
  }

  void Arena::renderAttacks() const
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

  void Arena::renderRunningMode() const
  {
    GameState::render();
    this->tileMap.render();
    this->renderPlayerLife();
    this->renderPlayedTime();
    this->cardSelectorDelayBar.render();

    for (Character *character : this->characters)
    {
      character->render();
    }

    this->renderAttacks();
    Global::attacksService->removeExpiredAttacks(); // TODO: Verify correct location of this method
  }

  void Arena::checkKeyboard()
  {
    if (
        this->arenaMode == ArenaMode::RUNNING &&
        this->canOpenCardSelector &&
        Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::Z))
    {
      Global::gameStateService->pushGameState(&this->cardSelector);
    }
  }

  void Arena::update()
  {
    this->checkKeyboard();

    if (this->arenaMode == ArenaMode::RUNNING)
    {
      for (Character *character : this->characters)
      {
        character->update();
      }

      this->updateAttacks();
      this->updateAnimations();
      this->cardSelectorDelayBar.update();
    }
  }

  void Arena::render() const
  {
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
    }
  }
}
