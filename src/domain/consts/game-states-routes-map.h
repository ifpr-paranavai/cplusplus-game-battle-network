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

    const std::map<GameStateRoute, std::function<GameState *(DefaultRouteParams)>> gameStatesRoutesMap = {
        {GameStateRoute::MAIN_MENU, [](DefaultRouteParams params)
         {
           return new MainMenu(); // Retorne um ponteiro bruto
         }},
        {GameStateRoute::ARENA, [](DefaultRouteParams params)
         {
           return new Arena(); // Retorne um ponteiro bruto
         }},
        {GameStateRoute::SCORE_BOARD, [](DefaultRouteParams params)
         {
           return new ScoreBoard(); // Retorne um ponteiro bruto
         }},
        {GameStateRoute::SCORE_REGISTER, [](DefaultRouteParams params)
         {
           try
           {
             if (params.has_value()) // Verifica se params contém um valor
             {
               // Converte o std::any armazenado em params->data para ScoreRegisterParams
               GameStateRouteParams<ScoreRegisterParams> convertedParams{
                   std::any_cast<ScoreRegisterParams>(params->data)};

               return new ScoreRegister(convertedParams); // Retorna um ponteiro bruto
             }
             else
             {
               throw std::runtime_error("Params não contém um valor.");
             }
           }
           catch (const std::bad_any_cast &e)
           {
             // Lida com o erro ao fazer o cast
             std::cerr << "Erro ao fazer cast: " << e.what() << std::endl;
             throw e; // Relança a exceção se necessário
           }
           catch (const std::exception &e)
           {
             // Lida com qualquer outro tipo de exceção
             std::cerr << "Erro: " << e.what() << std::endl;
             throw;
           }
         }}};
  }
}
