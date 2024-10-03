#pragma once
#include <string_view>
#include "../../dto/vector/vector.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../config/config.h"
#include "../../dto/color/color.h"
#include "../../../utils/subject/subject.h"
#include "../../../utils/observer/observer.h"

namespace Game
{
  class MenuOption
  {
  private:
    const std::string_view text;
    Color selectedColor = Color{239, 184, 16, 255};
    Subject<int> onClick;

  public:
    MenuOption(std::string_view text, Observer<int> *onClick) : text(text)
    {
      this->onClick.subscribe(onClick);
    };

    void render(const int yPosition, const bool isSelected);

    void click()
    {
      this->onClick.next(0);
    }
  };
}