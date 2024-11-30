#pragma once
#include <vector>
#include "../../cards/card/card.h"
#include "../../../styles/colors.h"

namespace Game
{
  struct CardSelectorCardsListConfig
  {
    const Vector position;
    const int width;
    const int height;
  };

  class CardSelectorCardsList
  {
  private:
    const Vector position;
    const int width;
    const int height;
    const int cardSize;
    const Vector initialCardPosition;

  public:
    CardSelectorCardsList(const CardSelectorCardsListConfig config);

    void render(std::vector<Card> cards, const int selectIndex) const;
    void resizeCardsIcons(std::vector<Card> &cards);
  };
}