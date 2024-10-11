#pragma once
#include "../../services/attacks-service/attacks-service.h"
#include "../../services/animation-service/animation-service.h"
#include "../../services/game-state-service/game-state-service.h"
#include "../../services/file-service/file-service.h"

namespace Game
{
    namespace Global
    {
        extern AttacksService *attacksService;
        extern AnimationService *animationService;
        extern GameStateService *gameStateService;
        extern FileService *fileService;
        void initializeGlobalServices();
        void cleanupGlobalServices();
    }
}