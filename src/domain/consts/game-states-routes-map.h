#pragma once

#include <map>
#include <functional>
#include <memory>
#include <optional>
#include "../enums/game-states-routes.h"
#include "../nodes/game-state/game-state.h"
#include "../scenes/game-states/main-menu/main-menu.h"
#include "../scenes/game-states/arena/arena.h"
#include "../scenes/game-states/score-board/score-board.h"
#include "../scenes/game-states/score-register/score-register.h"
#include "../scenes/game-states/pause/pause.h"

namespace Game
{
  namespace GameStateRoutes
  {

    const std::map<GameStateRoute, std::function<GameState *(DefaultRouteParams)>> gameStatesRoutesMap = {
        {GameStateRoute::MAIN_MENU, [](DefaultRouteParams params)
         {
           return new MainMenu();
         }},
        {GameStateRoute::ARENA, [](DefaultRouteParams params)
         {
           return new Arena();
         }},
        {GameStateRoute::SCORE_BOARD, [](DefaultRouteParams params)
         {
           return new ScoreBoard();
         }},
        {GameStateRoute::PAUSE, [](DefaultRouteParams params)
         {
           return new Pause();
         }},
        {GameStateRoute::SCORE_REGISTER, [](DefaultRouteParams params)
         {
           try
           {
             if (params.has_value())
             {

               GameStateRouteParams<ScoreRegisterParams> convertedParams{
                   std::any_cast<ScoreRegisterParams>(params->data)};
               return new ScoreRegister(convertedParams);
             }
             else
             {
               throw std::runtime_error("Params não contém um valor.");
             }
           }
           catch (const std::bad_any_cast &e)
           {
             std::cerr << "Erro ao fazer cast: " << e.what() << std::endl;
             throw e;
           }
           catch (const std::exception &e)
           {
             std::cerr << "Erro: " << e.what() << std::endl;
             throw;
           }
         }}};
  }
}
