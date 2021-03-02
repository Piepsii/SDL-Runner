// game_run.cc

#include <papaya.hpp>
#include "endless_runner.hpp"

#include <stdexcept>

int game_run()
{
   using namespace papaya;

   try { 
      Platform platform;
      Window window("papaya", 1024, 576);
      Debug::log("Platform and window ok!");

      Dispatcher dispatcher;
      Input input;
      FileSystem filesystem("lippuu", "papaya");
      TextureStorage textures(filesystem);
      Renderer renderer;

      if (!Graphics::init()) {
         throw std::runtime_error("Could not initialize Graphics!");
      }

      dispatcher.register_listener<KeyPressedEvent>(input);
      dispatcher.register_listener<KeyReleasedEvent>(input);
      dispatcher.register_listener<MouseMoveEvent>(input);
      dispatcher.register_listener<MouseButtonEvent>(input);
      dispatcher.register_listener<MouseWheelEvent>(input);

      Runtime runtime(dispatcher,
                      input,
                      filesystem,
                      textures,
                      renderer);

      runner::EndlessRunner *game = new runner::EndlessRunner(runtime);
      if( !game->init() )
      {
         Debug::log("failed to initialize game!");
         return 0;
      }

      bool running = true;
      while (running) {
         input.update();
         if (!dispatcher.update()) {
            running = false;
         }

         auto dt = runtime.deltaTime();
         if( !game->tick(dt) )
         {
            running = false;
         }

         window.present();
      }

      game->shut();
      delete game;

      Graphics::shut();
   } 
   catch (std::exception &e) {
      (void)e;
   }

   return 0;
}
