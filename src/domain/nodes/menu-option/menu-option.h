#pragma once
#include <string_view>
#include "../../dto/sound-effect/sound-effect.h"
#include "../../dto/vector/vector.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../config/config.h"
#include "../../dto/color/color.h"
#include "../../../utils/subject/subject.h"
#include "../../../utils/observer/observer.h"
#include "../../styles/colors.h"
#include "../ui-entity/ui-entity.h"

namespace Game
{
  struct MenuOptionConfig
  {
    const std::string_view text;
    const int yPosition;
    Observer<int> *onClick;
  };

  class MenuOption : public UIEntity
  {
  private:
    const SoundEffect selectSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/select.wav");
    const std::string_view text;

    bool isSelected = false;
    Subject<int> onClick;
    RenderTextData renderTextData;

    void initRenderTextData();

  public:
    MenuOption(const MenuOptionConfig &config);

    void render(const Vector &basePosition = {0, 0}) const override;

    void update() override {}

    void click()
    {
      Global::adaptersInstance.audioManager->playWavSoundEffect(this->selectSFX);
      this->onClick.next(0);
    }

    void setSelected(const bool isSelected);

    std::string_view getText() const
    {
      return this->text;
    }
  };
}