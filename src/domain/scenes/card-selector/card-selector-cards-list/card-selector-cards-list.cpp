#include "./card-selector-cards-list.h"

namespace Game
{
  CardSelectorCardsList::CardSelectorCardsList(const CardSelectorCardsListConfig config)
      : position(config.position),
        width(config.width),
        height(config.height),
        cardSize(config.width / 5 - 20),
        initialCardPosition(config.position + Vector{10, 10}) {}

  void CardSelectorCardsList::render(std::vector<Card> cards, const int selectIndex) const
  {
    for (size_t i = 0; i < cards.size(); i++)
    {
      const auto cardPosition = this->initialCardPosition + Vector((10 + this->cardSize) * i, 0);
      Global::adaptersInstance.renderer->renderBorder({cardPosition,
                                                       this->cardSize,
                                                       this->cardSize,
                                                       selectIndex == i ? Styles::Colors::SELECTED_COLOR : Color{0, 0, 0, 255}});
      const float iconHeight = cards[i].getIconSprite().getHeight();
      const float cardTopPadding = (this->cardSize - iconHeight) / 2;
      cards[i].getIconSprite().renderSprite(cardPosition + Vector{0, cardTopPadding});
    }
  }

  void CardSelectorCardsList::resizeCardsIcons(std::vector<Card> &cards)
  {
    for (auto &card : cards)
    {
      auto &iconSprite = card.getIconSprite();
      const float scale = this->cardSize / iconSprite.getWidth();
      card.setIconSpriteSize(this->cardSize, iconSprite.getHeight() * scale);
    }
  }
}