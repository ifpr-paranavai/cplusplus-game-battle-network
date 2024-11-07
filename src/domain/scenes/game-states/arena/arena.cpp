#include "arena.h"
#include <SDL2/SDL.h>

namespace Game
{

  Arena::Arena()
  {
    Global::adaptersInstance.audioManager->playMusic(this->music);
    this->cardSelectorDelayBar.subscribeToOnCompleteLoad(&this->unblockOpenCardSelectorHandler);
    this->cardSelector.subscribeToOnSelectCard(&this->closeCardSelectorDelayHandler);
    this->createEnemies();
    this->setPlayer(new Player());
    this->removeTutorialsTimer.subscribe(new RemoveTutorialsHandler(*this));
    this->removeTutorialsTimer.init(this->tutorialsDuration);
  }

  Arena::~Arena()
  {
    for (Actor *actor : this->actors)
    {
      delete actor;
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
    this->actors.push_back(enemy);
  }

  void Arena::setPlayer(Player *player)
  {
    this->player = player;
    this->player->setTilePosition({1, 1});
    this->player->setTileXLimit({0, static_cast<float>(this->tileMap.getPlayerColumnTilesCount() - 1)});
    this->player->setTileYLimit({0, static_cast<float>(this->tileMap.getTilesRowsCount() - 1)});
    this->player->subscribeToDeath(&this->gameOverHandler);
    this->actors.push_back(this->player);
    this->cardSelector.subscribeToOnSelectCard(this->player->getSetSelectedCardHandler());
  }

  void Arena::updateAttacks()
  {
    for (auto &projectile : Global::attacksService->getDynamicAttacks())
    {
      projectile->update();
    }

    for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
    {
      tileBasedAttack->update();
    }

    for (auto &projectile : Global::attacksService->getDynamicAttacks())
    {
      for (Actor *actor : this->actors)
      {
        projectile->checkCollision(actor);
        actor->checkCollision(projectile.get());
      }
    }

    for (auto &tileBasedAttack : Global::attacksService->getTileBasedAttacks())
    {
      for (Actor *actor : this->actors)
      {
        tileBasedAttack->checkCollision(actor);
        actor->checkCollision(tileBasedAttack.get());
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
        textHeight + 10,
        Color{0, 0, 0, 255},
    });
    textRenderer->renderText({lifeStr, {10.0f + 100.0f - textWidth, 15.0f}});
  }

  void Arena::renderPlayedTime() const
  {
    const float playedTime = Global::adaptersInstance.timeManager->getElapsedTime() - this->arenaStartedAt;
    auto textRenderer = Global::adaptersInstance.textRenderer;
    const auto playedTimeStr = TimeUtil::formatElapsedTime(playedTime);
    const int textWidth = textRenderer->getTextWidth(playedTimeStr);
    textRenderer->renderText({playedTimeStr, {Config::WINDOW_WIDTH - textWidth - 10.0f, 10.0f}});
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

  void Arena::renderTutorials() const
  {
    if (!this->showTutorials)
    {
      return;
    }

    for (int i = 0; i < this->tutorials.size(); i++)
    {
      const auto tutorial = this->tutorials[i];
      const int textWidth = Global::adaptersInstance.textRenderer->getTextWidth(tutorial);
      const int xPosition = Config::WINDOW_WIDTH / 2 - textWidth / 2;
      Global::adaptersInstance.textRenderer->renderText(
          {tutorial,
           {static_cast<float>(xPosition),
            static_cast<float>(this->initialTutorialYPosition + i * this->spaceBetweenTutorials)}});
    }
  }

  void Arena::checkKeyboard()
  {
    if (
        this->canOpenCardSelector &&
        Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::Z))
    {
      Global::gameStateService->pushGameStateModal(&this->cardSelector);
    }
  }

  void Arena::update()
  {
    this->checkKeyboard();
    this->removeTutorialsTimer.update();

    for (Actor *actor : this->actors)
    {
      actor->update();
    }

    this->updateAttacks();
    this->updateAnimations();
    this->cardSelectorDelayBar.update();
  }

  void Arena::render() const
  {
    GameState::render();
    this->tileMap.render();
    this->renderPlayerLife();
    this->renderPlayedTime();
    this->cardSelectorDelayBar.render();

    for (Actor *actor : this->actors)
    {
      actor->render();
    }

    this->renderAttacks();
    this->renderTutorials();
    Global::attacksService->removeExpiredAttacks(); // TODO: Verify correct location of this method
  }

}
