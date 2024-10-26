#pragma once
#include <string_view>
#include "../../../../config/config.h"
#include "../../../dto/vector/vector.h"
#include "../../../../utils/global-adapters/global-adapters.h"
#include "../../../dto/color/color.h"
#include "../../../../utils/subject/subject.h"
#include "../../../../utils/observer/observer.h"
#include "../../../nodes/game-state-modal/game-state-modal.h"
#include "../../../nodes/animated-visual-element/blinking-visual-element.h"
#include "../../../styles/colors.h"

namespace Game
{
  enum class RenderMode
  {
    LOADING,
    LOADED
  };

  class CardSelectorDelayBar : public GameStateModal
  {
  private:
    static constexpr float barHeight = 30;
    static constexpr float delayTime = 10;
    static constexpr float barWidth = Config::WINDOW_WIDTH / 2;
    static constexpr Color loadingBarColor = Styles::Colors::SELECTED_COLOR;

    const Vector barPosition = Vector(this->barWidth / 2, 10);
    const std::string helpText = "Pressione Z";
    const Vector textPosition = this->barPosition + Vector((this->barWidth - Global::adaptersInstance.textRenderer->getTextWidth(helpText)) / 2, 0);

    float delayTimer = 0;
    float loadingBarWidth = 0;
    float percentComplete = 0;
    Subject<int> onCompleteLoadSubject;
    BlinkingVisualElement blingkingBar = BlinkingVisualElement({this->barWidth,
                                                                this->barHeight,
                                                                this->loadingBarColor,
                                                                0.25f,
                                                                Color{255, 255, 255, 255},
                                                                0.25f});

    void updateDelayTimer();
    void updatePercentCompleted();
    void renderBorder() const;
    void renderLoadingBar() const;

  public:
    void update() override;
    void render() const override;

    void subscribeToOnCompleteLoad(Observer<int> *observer)
    {
      this->onCompleteLoadSubject.subscribe(observer);
    }

    void resetTimer()
    {
      this->delayTimer = 0;
    }
  };
}