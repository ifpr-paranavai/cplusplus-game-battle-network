#include "pause.h"

namespace Game
{
  Pause::Pause() : Menu({"Pausado",
                         {{"Continuar", new ContinueHandler()},
                          {"Menu Principal", new BackToMainMenuHandler()},
                          {"Sair", new QuitHandler()}}})
  {
  }

}