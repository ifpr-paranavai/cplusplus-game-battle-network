#pragma once
#include <string_view>
#include <optional>
#include "../../domain/dto/vector/vector.h"
#include "../../domain/dto/color/color.h"

namespace Game
{

  struct RenderTextData
  {
    std::string_view text;
    Vector position;
    std::optional<int> fontSize;
    std::optional<int> maxWidth;
    std::optional<Color> color;
  };

  class TextRendererPort
  {
  public:
    virtual int getTextHeight(std::string_view text) = 0;
    virtual int getTextWidth(std::string_view text) = 0;
    virtual void renderText(const RenderTextData &renderTextData) = 0;
  };
}