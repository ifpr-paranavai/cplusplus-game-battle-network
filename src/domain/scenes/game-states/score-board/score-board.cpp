#include "score-board.h"

namespace Game
{

  ScoreBoard::ScoreBoard()
  {
    this->loadScoresFromFile();
    this->sortScores();
    this->calcScoreLineXPosition();
    this->backOption.setSelected(true);
  }

  void ScoreBoard::sortScores()
  {
    std::sort(scores.begin(), scores.end(),
              [](Score *a, Score *b)
              {
                return TimeUtil::formatedElapsedTimeToInt(a->getElapsedTime()) <
                       TimeUtil::formatedElapsedTimeToInt(b->getElapsedTime());
              });
  }

  void ScoreBoard::loadScoresFromFile()
  {
    const auto fileDataScores = Global::fileService->loadFromBinaryFile("score_board");
    this->scores.reserve(fileDataScores.size());
    for (const auto &fileDataScore : fileDataScores)
    {
      scores.push_back(new Score(Score::fromFileData(fileDataScore)));
    }
  }

  void ScoreBoard::calcScoreLineXPosition()
  {
    if (this->scores.size() == 0)
    {
      return;
    }

    this->scoreLineXPosition = (Config::WINDOW_WIDTH / 2) - (Global::adaptersInstance.textRenderer->getTextWidth(this->getScoreLine(this->scores[0])) / 2);
  }

  void ScoreBoard::verifyCommands()
  {
    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ENTER))
    {
      this->backOption.click();
    }
  }

  std::string ScoreBoard::getScoreLine(const Score *score) const
  {
    return score->getCreatedAt() + " - " + score->getPlayerName() + " - " + score->getElapsedTime();
  }

  void ScoreBoard::renderScores() const
  {
    for (size_t i = 0; i < this->scoresPerPage && i < this->scores.size(); ++i)
    {
      auto &score = this->scores[i];
      Global::adaptersInstance.textRenderer->renderText(
          {this->getScoreLine(score),
           {static_cast<float>(this->scoreLineXPosition), static_cast<float>((this->spaceBetweenElements * (i + 1)))}});
    }
  }

  void ScoreBoard::update()
  {
    this->verifyCommands();
  }

  void ScoreBoard::render(const Vector &basePosition) const
  {
    GameState::render(basePosition);
    this->renderScores();
    this->backOption.render();
  }
}