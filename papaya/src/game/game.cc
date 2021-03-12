// game.cc

#include "game/game.hpp"
#include "game/runtime.hpp"
#include "game/state.hpp"
#include "platform/time.hpp"
#include "input/input.hpp"

namespace papaya {
   Game::Game(Runtime &runtime)
      : runtime_(runtime)
      , current_(nullptr)
   {
   }
   
   bool Game::init()
   {
      return true;
   }

   void Game::shut()
   {
   }

   bool Game::tick(const Time &deltatime)
   {
      if (current_ == nullptr) {
         return false;
      }

      if (!current_->update(deltatime)) {
         State *next = current_->next();
         if (next == nullptr) {
            return false;
         }

         current_ = next;
      }

      current_->render(runtime_.renderer());

      return true;
   }

   void Game::set_active_state(State *state)
   {
      current_ = state;
   }
} // !papaya
