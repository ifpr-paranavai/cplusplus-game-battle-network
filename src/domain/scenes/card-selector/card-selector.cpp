#include "card-selector.h"

namespace Game
{
  void CardSelector::renderContainer()
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

  void CardSelector::renderCardViewer()
  {
    Global::adaptersInstance.renderer->renderBorder({this->cardViewerPosition,
                                                     this->insideContainerWidth,
                                                     this->insideContainerHeight,
                                                     Color{0, 0, 0, 255}});
  }

  void CardSelector::renderCardsList()
  {
    Global::adaptersInstance.renderer->renderBorder({this->cardsListPosition,
                                                     this->insideContainerWidth,
                                                     this->insideContainerHeight,
                                                     Color{0, 0, 0, 255}});
    this->renderCardInListContainer();
  }

  void CardSelector::renderCardInListContainer()
  {
    const auto initialCardPosition = this->cardsListPosition + Vector(10, 10);
    const auto cardSize = (this->insideContainerWidth / 10) - this->insideContainersPadding * 2;

    for (size_t i = 0; i < this->cardCount; i++)
    {
      Global::adaptersInstance.renderer->renderBorder({initialCardPosition + (Vector((10 + cardSize) * i, 0)),
                                                       cardSize,
                                                       cardSize,
                                                       this->selectIndex == i ? Color{239, 184, 16, 255} : Color{0, 0, 0, 255}});
    }
  }

  void CardSelector::update()
  {
    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_RIGHT) && this->selectIndex < this->cardCount - 1)
    {
      this->selectIndex++;
    }
    if (Global::adaptersInstance.keyboardManager->isKeyPressed(KeyCode::ARROW_LEFT) && this->selectIndex > 0)
    {
      this->selectIndex--;
    }
  }

  void CardSelector::render()
  {
    this->renderContainer();
    this->renderCardViewer();
    this->renderCardsList();
  }

}