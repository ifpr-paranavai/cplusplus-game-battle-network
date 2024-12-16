#pragma once
#include "../../../nodes/game-state/game-state.h"
#include "../../../dto/vector/vector.h"
#include "../../../global/global-services/global-services.h"
#include "../../../nodes/menu-option/menu-option.h"
#include "../../../../config/config.h"

namespace Game
{
  class GoToMainMenuHandler : public Observer<int>
  {
  public:
    void next(const int &value) override
    {
      Global::gameStateService->replace(GameStateRoute::MAIN_MENU);
    }
  };

  class CreditsState : public GameState
  {
  private:
    static constexpr int titleFontSize = 40;
    static constexpr int creditsTextFontSize = 26;
    static constexpr int topPadding = 100;
    static constexpr int spacing = 50;

    const std::string title = "Créditos";
    const std::string creditsText = "Jogo desenvolvido como Trabalho de Conclusão de Curso do curso de Bacharelado em Engenharia de Software\n\n"
                                    "Desenvolvedor: Jonatas S. Oliveira\n"
                                    "Orientador: Eduardo H. M. Cruz\n"
                                    "Obrigado por jogar!";
    const int backOptionYPostion = Config::WINDOW_HEIGHT - Global::adaptersInstance.textRenderer->getTextHeight("Voltar") - 10;
    const int titleWidth = Global::adaptersInstance.textRenderer->getTextWidth(this->title, this->titleFontSize);
    const Vector titlePosition = {
        static_cast<float>(Config::WINDOW_WIDTH) / 2.0f - static_cast<float>(titleWidth) / 2.0f,
        static_cast<float>(this->topPadding)};
    const Vector creditsPosition = {this->spacing, this->titlePosition.y + this->spacing};
    const int creditsMaxWidth = Config::WINDOW_WIDTH - this->spacing * 2.0f;

    MenuOption backOption = MenuOption({"Voltar", this->backOptionYPostion, new GoToMainMenuHandler()});

    void verifyCommands();

  public:
    CreditsState() { this->backOption.setSelected(true); }

    void update() override { this->verifyCommands(); }
    void render(const Vector &basePosition = {0, 0}) const override;
  };
}
