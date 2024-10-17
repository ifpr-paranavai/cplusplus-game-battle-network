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

    void renderCardViewer(const Card &selectedCard) const;
    void renderCardText(const Card &selectedCard) const;

  public:
    CardSelectorViewer(const CardSelectorViewerConfig config);

    void render(const Card &selectedCard) const;
    void resizeCardsSprites(std::vector<Card> &cards);
  };
};