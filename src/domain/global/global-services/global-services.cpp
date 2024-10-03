#include "global-services.h"

namespace Game
{
    namespace Global
    {
        AttacksService *attacksService = nullptr;
        AnimationService *animationService = nullptr;
        GameStateService *gameStateService = nullptr;

        void initializeGlobalServices()
        {
            attacksService = new AttacksService();
            animationService = new AnimationService();
            gameStateService = new GameStateService();
        }

        void cleanupGlobalServices()
        {
            delete attacksService;
            delete animationService;
            delete gameStateService;
            attacksService = nullptr;
            animationService = nullptr;
            gameStateService = nullptr;
        }
    }
}