#include "card-selector-viewer.h"

namespace Game
{
  CardSelectorViewer::CardSelectorViewer(const CardSelectorViewerConfig config)
      : position(config.position),
        width(config.width),
        height(config.height),
        viewerSize(config.width * 0.4f),
        textPosition({config.position.x + 10, config.position.y + config.width * 0.4f + 10}),
        viewerPosition(config.position + Vector{(config.width - config.width * 0.4f) / 2, 10})
  {
  }

  void CardSelectorViewer::renderCardViewer(Card &selectedCard)
  {
    Global::adaptersInstance.renderer->renderBorder(
        {this->viewerPosition,
         this->viewerSize,
         this->viewerSize,
         Color{255, 255, 255, 255}});
    const float spriteHeight = selectedCard.getCardSprite().getHeight();
    const float viewerTopPadding = (this->viewerSize - spriteHeight) / 2;
    selectedCard.getCardSprite().renderSprite(this->viewerPosition + Vector{0, viewerTopPadding});
  }

  void CardSelectorViewer::renderCardText(Card &selectedCard)
  {
    const int textHeight = Global::adaptersInstance.renderer->getTextHeight(selectedCard.getName());
    Global::adaptersInstance.renderer->renderText({selectedCard.getName(), this->textPosition});
    const int textWidth = Global::adaptersInstance.renderer->getTextWidth(selectedCard.getDescription());
    Global::adaptersInstance.renderer->renderText({selectedCard.getDescription(),
                                                   this->textPosition + Vector{0, textHeight + 10},
                                                   16,
                                                   this->width});
  }

  void CardSelectorViewer::render(Card &selectedCard)
  {
    this->renderCardViewer(selectedCard);
    this->renderCardText(selectedCard);
  }

  void CardSelectorViewer::resizeCardsSprites(std::vector<Card> &cards)
  {
    for (auto &card : cards)
    {
      const float scale = this->viewerSize / card.getCardSprite().getWidth();
      card.getCardSprite().setWidth(this->viewerSize);
      card.getCardSprite().setHeight(card.getCardSprite().getHeight() * scale);
    }
  }
};