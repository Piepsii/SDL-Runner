// game_run.cc

#include <papaya.hpp>
#include "endless_runner.hpp"

#include <stdexcept>
#include <ctime>

using namespace papaya;

int game_run()
{
   try { 
      int width = 854;
      int height = 480;
      Platform platform;
      Window window("5sd13_2020 - Endless Runner - Paul Brandstetter", width, height);
      Debug::log("Platform and window ok!");

      Dispatcher dispatcher;
      Input input;
      FileSystem filesystem("Piepsii", "papaya");
      TextureStorage textures(filesystem);
      Renderer renderer;

      if (!Graphics::init(width, height)) {
         throw std::runtime_error("Could not initialize Graphics!");
      }

      dispatcher.register_listener<KeyPressedEvent, Input>(input);
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

      std::srand(static_cast<unsigned int>(std::time(nullptr)));

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

         renderer.flush();
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
