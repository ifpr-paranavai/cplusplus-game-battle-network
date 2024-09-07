#pragma once
#include "../../cards/card/card.h"
#include "../../../dto/vector/vector.h"
#include <vector>

namespace Game
{
  struct CardSelectorViewerConfig
  {
    const Vector position;
    const float width;
    const float height;
  };

  class CardSelectorViewer
  {
  private:
    const Vector position;
    const float width;
    const float height;
    const float viewerSize;
    const Vector textPosition;
    const Vector viewerPosition;

    void renderCardViewer(Card &selectedCard);
    void renderCardText(Card &selectedCard);

  public:
    CardSelectorViewer(const CardSelectorViewerConfig config);

    void render(Card &selectedCard);
    void resizeCardsSprites(std::vector<Card> &cards);
  };
};