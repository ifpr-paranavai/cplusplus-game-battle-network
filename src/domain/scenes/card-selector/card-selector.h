#pragma once
#include <vector>
#include "../../../utils/global-adapters/global-adapters.h"
#include "../../../config/config.h"
#include "../../dto/vector/vector.h"
#include "../../nodes/weapon/weapon.h"
#include "../cards/card/card.h"
#include "../../../utils/subject/subject.h"
#include "../cards/sword-card/sword-card.h"   // TODO: remover daqui
#include "../cards/sniper-card/sniper-card.h" // TODO: remover daqui
#include "./card-selector-viewer/card-selector-viewer.h"
#include "./card-selector-cards-list/card-selector-cards-list.h"
#include "../../nodes/game-state-modal/game-state-modal.h"
#include "../../dto/sound-effect/sound-effect.h"

namespace Game
{
  class CardSelector : public GameStateModal
  {
  private:
    static constexpr int insideContainersPadding = 10;
    static constexpr int containerWidth = Config::WINDOW_WIDTH / 2;
    static constexpr int containerHeight = Config::WINDOW_HEIGHT;

    const SoundEffect selectSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/select.wav");
    const int insideContainerHeight = (this->containerHeight / 2) - 2 * this->insideContainersPadding;
    const int insideContainerWidth = this->containerWidth - this->insideContainersPadding * 2;

    int selectIndex = 0;
    std::vector<Card> cards;
    Subject<Card> onSelectCardSubject;

    CardSelectorViewer cardSelectorViewer = CardSelectorViewer({{this->insideContainersPadding,
                                                                 this->insideContainersPadding},
                                                                this->insideContainerWidth,
                                                                this->insideContainerHeight});
    CardSelectorCardsList cardSelectorCardsList = CardSelectorCardsList(
        {{static_cast<float>(this->insideContainersPadding), static_cast<float>(this->insideContainersPadding + this->insideContainerHeight)},
         this->insideContainerWidth,
         this->insideContainerHeight});

    void selectCard();
    void renderContainer() const;

  public:
    CardSelector();
    void update() override;
    void render() const override;

    void subscribeToOnSelectCard(Observer<Card> *observer)
    {
      this->onSelectCardSubject.subscribe(observer);
    }
  };
}