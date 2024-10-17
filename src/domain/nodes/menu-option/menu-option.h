#pragma once
#include <string_view>
#include "../../dto/vector/vector.h"
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../config/config.h"
#include "../../dto/color/color.h"
#include "../../../utils/subject/subject.h"
#include "../../../utils/observer/observer.h"
#include "../../styles/colors.h"

namespace Game
{
  class MenuOption
  {
  private:
    const std::string_view text;
    Subject<int> onClick;

  public:
    MenuOption(const std::string_view text, Observer<int> *onClick) : text(text)
    {
      this->onClick.subscribe(onClick);
    };

    void render(const int yPosition, const bool isSelected) const;

    void click()
    {
      this->onClick.next(0);
    }

    std::string_view getText()
    {
      return this->text;
    }
  };
}