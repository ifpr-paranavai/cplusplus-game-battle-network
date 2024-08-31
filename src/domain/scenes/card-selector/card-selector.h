#pragma once
#include <vector>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../config/config.h"
#include "../../dto/vector/vector.h"
#include "../../nodes/weapon/weapon.h"

namespace Game
{
  class CardSelector
  {
  private:
    const float insideContainersPadding = 10;
    const float containerWidth = Config::WINDOW_WIDTH / 2;
    const float containerHeight = Config::WINDOW_HEIGHT;
    const float insideContainerHeight = (this->containerHeight / 2) - 2 * this->insideContainersPadding;
    const float insideContainerWidth = this->containerWidth - this->insideContainersPadding * 2;
    const Vector cardViewerPosition = {this->insideContainersPadding, this->insideContainersPadding};
    const Vector cardsListPosition = {
        this->insideContainersPadding, this->insideContainersPadding + this->insideContainerHeight};
    const int cardCount = 10;
    int selectIndex = 0;

    void renderContainer();
    void renderCardViewer();
    void renderCardsList();
    void renderCardInListContainer();

  public:
    void render();
    void update();
  };
}