#include "card.h"

namespace Game
{
  Card::Card(const CardConfig cardConfig) : name(cardConfig.name),
                                            description(cardConfig.description),
                                            weaponFactory(cardConfig.weaponFactory),
                                            iconSprite(cardConfig.iconSprite),
                                            cardSprite(cardConfig.iconSprite)
  {
  }
}