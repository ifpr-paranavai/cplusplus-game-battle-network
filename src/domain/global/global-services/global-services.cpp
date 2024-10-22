#include "global-services.h"

namespace Game
{
    namespace Global
    {
        AttacksService *attacksService = nullptr;
        AnimationService *animationService = nullptr;
        GameStateService *gameStateService = nullptr;
        FileService *fileService = nullptr;

        void initializeGlobalServices()
        {
            attacksService = new AttacksService();
            animationService = new AnimationService();
            gameStateService = new GameStateService();
            fileService = new FileService();
        }

        void cleanupGlobalServices()
        {
            delete attacksService;
            delete animationService;
            delete gameStateService;
            delete fileService;
            attacksService = nullptr;
            animationService = nullptr;
            gameStateService = nullptr;
            fileService = nullptr;
        }
    }
}