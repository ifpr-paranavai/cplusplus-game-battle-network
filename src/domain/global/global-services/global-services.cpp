#include "global-services.h"

namespace Game
{
    namespace Global
    {
        AttacksService *attacksService = nullptr;
        AnimationService *animationService = nullptr;

        void initializeGlobalServices()
        {
            attacksService = new AttacksService();
            animationService = new AnimationService();
        }

        void cleanupGlobalServices()
        {
            delete attacksService;
            delete animationService;
            attacksService = nullptr;
            animationService = nullptr;
        }
    }
}