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

  void CardSelectorViewer::renderCardViewer(const Card &selectedCard) const
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

  void CardSelectorViewer::renderCardText(const Card &selectedCard) const
  {
    auto textRenderer = Global::adaptersInstance.textRenderer;
    const int textHeight = textRenderer->getTextHeight(selectedCard.getName());
    textRenderer->renderText({selectedCard.getName(), this->textPosition});
    const int textWidth = textRenderer->getTextWidth(selectedCard.getDescription());
    textRenderer->renderText({selectedCard.getDescription(),
                              this->textPosition + Vector{0.0f, textHeight + 10.0f},
                              16,
                              this->width});
  }

  void CardSelectorViewer::render(const Card &selectedCard) const
  {
    this->renderCardViewer(selectedCard);
    this->renderCardText(selectedCard);
  }

  void CardSelectorViewer::resizeCardsSprites(std::vector<Card> &cards)
  {
    for (auto &card : cards)
    {
      const float scale = this->viewerSize / card.getCardSprite().getWidth();
      card.setSpriteSize(this->viewerSize, card.getCardSprite().getHeight() * scale);
    }
  }
};