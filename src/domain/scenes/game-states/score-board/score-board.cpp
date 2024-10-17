#include "score-board.h"

namespace Game
{

  ScoreBoard::ScoreBoard()
  {
    this->loadScoresFromFile();
  }

  void ScoreBoard::loadScoresFromFile()
  {
    const auto fileDataScores = Global::fileService->loadFromBinaryFile("score_board");
    for (const auto &fileDataScore : fileDataScores)
    {
      this->scores.push_back(Score::fromFileData(fileDataScore));
    }
  }

  void ScoreBoard::verifyCommands()
  {
    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ENTER))
    {
      this->backOption.click();
    }
  }

  void ScoreBoard::update()
  {
    this->verifyCommands();
  }

  void ScoreBoard::render() const
  {
    GameState::render();
    for (const auto &score : this->scores)
    {
      auto scoreStr = score.getCreatedAt() + " - " + score.getPlayerName() + " - " + score.getElapsedTime();
      Global::adaptersInstance.textRenderer->renderText({scoreStr, {0, 0}});
    }
    this->backOption.render(this->backOptionYPostion, true);
  }
}