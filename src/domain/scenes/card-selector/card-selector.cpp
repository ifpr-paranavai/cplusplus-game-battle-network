#include "card-selector.h"

namespace Game
{
  CardSelector::CardSelector()
  {
    this->cards.reserve(2);
    this->cards.push_back(SwordCard());
    this->cards.push_back(SniperCard());
    this->cardSelectorViewer.resizeCardsSprites(this->cards);
    this->cardSelectorCardsList.resizeCardsIcons(this->cards);
  }

  void CardSelector::renderContainer() const
  {
    Global::adaptersInstance.renderer->renderElement({{0, 0},
                                                      this->containerWidth,
                                                      this->containerHeight,
                                                      Color{0, 0, 255, 255}});
    Global::adaptersInstance.renderer->renderBorder({{0, 0},
                                                     this->containerWidth,
                                                     this->containerHeight,
                                                     Color{255, 255, 255, 255}});
  }

  void CardSelector::selectCard()
  {
    Global::adaptersInstance.audioManager->playWavSoundEffect(this->selectSFX);
    this->onSelectCardSubject.next(this->cards[this->selectIndex]);
  }

  void CardSelector::update()
  {
    if (
        Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT) &&
        this->selectIndex < this->cards.size() - 1)
    {
      this->selectIndex++;
    }
    if (
        Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT) &&
        this->selectIndex > 0)
    {
      this->selectIndex--;
    }
    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::X))
    {
      this->selectCard();
    }
  }

  void CardSelector::render() const
  {
    this->renderContainer();
    this->cardSelectorViewer.render(this->cards[this->selectIndex]);
    this->cardSelectorCardsList.render(this->cards, this->selectIndex);
  }
}