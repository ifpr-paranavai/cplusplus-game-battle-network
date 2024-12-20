#pragma once
#include <string>
#include <vector>
#include "../../../nodes/game-state/game-state.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../../config/config.h"
#include "../../../dto/vector/vector.h"
#include "../../../styles/colors.h"
#include "../../../nodes/sprite/sprite.h"
#include "../../../../utils/time/time.h"
#include "../../../../utils/date/date.h"
#include "../../../dto/score/score.h"
#include "./score-register-params.h"

namespace Game
{

  class ScoreRegister : public GameState
  {
  private:
    static constexpr int fontSize = 40;
    static constexpr int spaceBetweenElements = 10;

    std::array<std::string, 3> playerNameLetters = {"A", "A", "A"};

    const std::string congratulationsText = "Parabéns, você venceu!";
    const std::string registerText = "Salvar";
    const std::string tutorialText = "Setas - Mover cursor / Alterar letra | Enter - Confirmar";
    const int letterHeight = Global::adaptersInstance.textRenderer->getTextHeight("A", this->fontSize);
    const int letterWidth = Global::adaptersInstance.textRenderer->getTextWidth("A", this->fontSize);
    const int qtdNameLetters = sizeof(this->playerNameLetters) / sizeof(this->playerNameLetters[0]);
    const int maxIndex = qtdNameLetters;
    const int letterYPosition = Config::WINDOW_HEIGHT / 2 - this->letterHeight / 2;
    const int registerTextWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->registerText, this->fontSize);
    const int totalWidth = this->registerTextWidth + this->letterWidth * 3 + this->spaceBetweenElements;
    const int initialXPosition = (Config::WINDOW_WIDTH - totalWidth) / 2;
    const int topTrianglePosition = this->letterYPosition - this->letterWidth - this->spaceBetweenElements;
    const int bottomTrianglePosition = this->letterYPosition + this->letterHeight + this->spaceBetweenElements;
    const int playedTimeTopPosition = this->topTrianglePosition - this->spaceBetweenElements - this->letterHeight;
    const float playedTime;
    const RenderTextData congratulationsTextData = {
        this->congratulationsText,
        {static_cast<float>(Config::WINDOW_WIDTH / 2 - Global::adaptersInstance.textRenderer->getTextWidth(this->congratulationsText) / 2),
         static_cast<float>(this->playedTimeTopPosition - this->spaceBetweenElements - this->letterHeight)},
        this->fontSize};
    const Vector tutorialPosition = {
        static_cast<float>(Config::WINDOW_WIDTH) / 2.0f - static_cast<float>(Global::adaptersInstance.textRenderer->getTextWidth(this->tutorialText)) / 2.0f,
        Config::WINDOW_HEIGHT - Global::adaptersInstance.textRenderer->getTextHeight(this->tutorialText) - 10};

    std::string textTime;
    RenderTextData playedTimeTextData;

    int selectedLetterIndex = 0;
    Sprite triagleSprite = Sprite({this->letterWidth,
                                   this->letterWidth,
                                   "assets/sprites/misc/triangle.png",
                                   false,
                                   Vector(0, 0)});
    Sprite downTriagleSprite = Sprite({this->letterWidth,
                                       this->letterWidth,
                                       "assets/sprites/misc/triangle.png",
                                       false,
                                       Vector(0, 0),
                                       std::nullopt,
                                       true});
    std::vector<int> letterXPositions;
    RenderTextData registerBtnTextData = {
        this->registerText,
        {static_cast<float>(this->calcXPositionByLetterIndex(this->maxIndex)), static_cast<float>(this->letterYPosition)},
        this->fontSize};

    void initPlayedTimeTextData();
    void verifyCommands();
    void incrementLetter();
    void decrementLetter();
    void saveScore();
    std::string getPlayerName() const;
    void renderPlayedTime() const;
    void renderTriangles() const;
    void renderPlayerName() const;
    void renderCreateBtn() const;
    void renderTutorial() const;

    int calcXPositionByLetterIndex(const int index) const
    {
      return this->initialXPosition + (this->letterWidth + this->spaceBetweenElements) * index;
    }

  public:
    ScoreRegister(GameStateRouteParams<ScoreRegisterParams> params);

    void update() override;
    void render(const Vector &basePosition = {0, 0}) const override;
  };
}