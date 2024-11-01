#pragma once
#include <vector>
#include <algorithm>
#include <any>
#include "../../../nodes/game-state/game-state.h"
#include "../../../global/global-services/global-services.h"
#include "../../../dto/score/score.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../../utils/observer/observer.h"
#include "../../../../config/config.h"
#include "../../../../utils/time/time.h"

namespace Game
{

  class BackHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->replace(GameStateRoute::MAIN_MENU);
    }
  };

  class ScoreBoard : public GameState
  {
  private:
    static constexpr int scoresPerPage = 15;
    const int spaceBetweenElements = 10 + Global::adaptersInstance.textRenderer->getTextHeight("A");
    const int backOptionYPostion = Config::WINDOW_HEIGHT - Global::adaptersInstance.textRenderer->getTextHeight("Voltar") - 10;

    std::vector<Score *> scores;
    MenuOption backOption = MenuOption({"Voltar", this->backOptionYPostion, new BackHandler()});
    int currentPage = 1;
    int scoreLineXPosition = 0;

    void calcScoreLineXPosition();
    void loadScoresFromFile();
    void sortScores();
    void verifyCommands();
    void renderScores() const;
    std::string getScoreLine(const Score *score) const;

  public:
    ScoreBoard();
    ~ScoreBoard()
    {
      for (Score *score : this->scores)
      {
        delete score;
      }
    }
    void update() override;
    void render() const override;
  };
}