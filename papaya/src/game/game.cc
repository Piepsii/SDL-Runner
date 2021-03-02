#include "game/game.hpp"
#include "game/runtime.hpp"
#include "platform/time.hpp"

#include "input/input.hpp"

namespace papaya
{
   Game::Game(Runtime &runtime)
      : runtime_(runtime)
   {

   }

   bool Game::init()
   {
       return true;
   }

   void Game::shut()
   {
   }

   bool Game::tick(const Time &deltaTime)
   {
      if( runtime_.input().keyboard().released(Key::Escape) )
         return false;

       return true;
   }
} // ! papaya