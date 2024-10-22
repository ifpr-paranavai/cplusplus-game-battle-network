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
#include "../../nodes/game-state/game-state.h"
#include "../../dto/sound-effect/sound-effect.h"

namespace Game
{
  class CardSelector : public GameState
  {
  private:
    const SoundEffect selectSFX = Global::adaptersInstance.audioManager->initSoundEffect("assets/sounds/select.wav");
    const float insideContainersPadding = 10;
    const float containerWidth = Config::WINDOW_WIDTH / 2;
    const float containerHeight = Config::WINDOW_HEIGHT;
    const float insideContainerHeight = (this->containerHeight / 2) - 2 * this->insideContainersPadding;
    const float insideContainerWidth = this->containerWidth - this->insideContainersPadding * 2;
    int selectIndex = 0;
    std::vector<Card> cards;
    Subject<Card> onSelectCardSubject;

    CardSelectorViewer cardSelectorViewer = CardSelectorViewer({{this->insideContainersPadding,
                                                                 this->insideContainersPadding},
                                                                this->insideContainerWidth,
                                                                this->insideContainerHeight});
    CardSelectorCardsList cardSelectorCardsList = CardSelectorCardsList(
        {{this->insideContainersPadding, this->insideContainersPadding + this->insideContainerHeight},
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