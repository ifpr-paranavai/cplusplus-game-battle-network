#include "score-register.h"

namespace Game
{
  ScoreRegister::ScoreRegister(const float _playedTime) : playedTime(_playedTime)
  {
    this->initPlayedTimeTextData();
    for (int i = 0; i < this->qtdNameLetters; i++)
    {
      this->letterXPositions.push_back(this->calcXPositionByLetterIndex(i));
    }
  }

  void ScoreRegister::initPlayedTimeTextData()
  {
    this->playedTimeTextData.text = "Tempo: " + TimeUtil::formatElapsedTime(this->playedTime);
    const int textWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->playedTimeTextData.text, this->fontSize);
    this->playedTimeTextData.fontSize = this->fontSize;
    this->playedTimeTextData.position = {Config::WINDOW_WIDTH / 2 - textWidth / 2, this->playedTimeTopPosition};
  }

  void ScoreRegister::incrementLetter()
  {
    char &currentLetter = this->playerNameLetters[this->selectedLetterIndex][0];
    if (currentLetter == 'Z')
    {
      currentLetter = 'A';
    }
    else
    {
      currentLetter++;
    }
  }

  void ScoreRegister::decrementLetter()
  {
    char &currentLetter = this->playerNameLetters[this->selectedLetterIndex][0];
    if (currentLetter == 'A')
    {
      currentLetter = 'Z';
    }
    else
    {
      currentLetter--;
    }
  }

  void ScoreRegister::verifyCommands()
  {
    auto keyboardManager = Global::adaptersInstance.keyboardManager;
    if (keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT) && this->selectedLetterIndex > 0)
    {
      this->selectedLetterIndex--;
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT) && this->selectedLetterIndex < this->maxIndex)
    {
      this->selectedLetterIndex++;
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_UP))
    {
      this->incrementLetter();
    }
    else if (keyboardManager->isKeyPressed(KeyCode::ARROW_DOWN))
    {
      this->decrementLetter();
    }
  }

  void ScoreRegister::renderPlayedTime() const
  {
    Global::adaptersInstance.textRenderer->renderText(this->playedTimeTextData);
  }

  void ScoreRegister::renderTriangles() const
  {
    if (this->selectedLetterIndex == this->maxIndex)
    {
      return;
    }
    const int positionX = this->letterXPositions.at(this->selectedLetterIndex);
    this->triagleSprite.renderSprite({positionX, this->topTrianglePosition});
    this->triagleSprite.renderSprite({positionX, this->bottomTrianglePosition}, true);
  }

  void ScoreRegister::renderPlayerName() const
  {
    RenderTextData renderTextData;
    renderTextData.fontSize = this->fontSize;

    for (size_t i = 0; i < this->qtdNameLetters; i++)
    {
      renderTextData.text = this->playerNameLetters[i];
      renderTextData.position = {this->letterXPositions.at(i), this->letterYPosition};
      if (this->selectedLetterIndex == i)
      {
        renderTextData.color = Styles::Colors::SELECTED_COLOR;
      }
      else
      {
        renderTextData.color = std::nullopt;
      }
      Global::adaptersInstance.textRenderer->renderText(renderTextData);
    }
  }

  void ScoreRegister::renderCreateBtn() const
  {
    RenderTextData renderTextData = this->registerBtnTextData;
    if (this->selectedLetterIndex == this->maxIndex)
    {
      renderTextData.color = Styles::Colors::SELECTED_COLOR;
    }
    Global::adaptersInstance.textRenderer->renderText(renderTextData);
  }

  void ScoreRegister::update()
  {
    this->verifyCommands();
  }

  void ScoreRegister::render() const
  {
    GameState::render();
    this->renderPlayedTime();
    this->renderTriangles();
    this->renderPlayerName();
    this->renderCreateBtn();
  }

}