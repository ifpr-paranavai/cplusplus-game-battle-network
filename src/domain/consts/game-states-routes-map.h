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

namespace Game
{
  namespace GameStateRoutes
  {
    using OpRouteParam = std::optional<GameStateRouteParams<std::any>>;

    const std::map<GameStateRoute, std::function<GameState *(OpRouteParam)>> gameStatesRoutesMap = {
        {GameStateRoute::MAIN_MENU, [](OpRouteParam params)
         {
           return new MainMenu(); // Retorne um ponteiro bruto
         }},
        {GameStateRoute::ARENA, [](OpRouteParam params)
         {
           return new Arena(); // Retorne um ponteiro bruto
         }},
        {GameStateRoute::SCORE_BOARD, [](OpRouteParam params)
         {
           return new ScoreBoard(); // Retorne um ponteiro bruto
         }},
        {GameStateRoute::SCORE_REGISTER, [](OpRouteParam params)
         {
           try
           {
             auto scoreRegisterParams = std::any_cast<ScoreRegisterParams>(params->data);
             return new ScoreRegister({scoreRegisterParams}); // Retorne um ponteiro bruto
           }
           catch (const std::bad_any_cast &e)
           {
             // Lidar com o erro aqui, por exemplo, logar uma mensagem
             std::cerr << "Erro ao fazer cast: " << e.what() << std::endl;
             throw e;
           } // Retorne um ponteiro bruto
         }}};
  }
}
