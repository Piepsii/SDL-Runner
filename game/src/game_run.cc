// game_run.cc

#include <papaya.hpp>
#include "endless_runner.hpp"

#include <stdexcept>

using namespace papaya;

int game_run()
{
   try { 
      Platform platform;
      Window window("5sd13_2020 - Endless Runner - Paul Brandstetter", 1280, 720);
      Debug::log("Platform and window ok!");

      Dispatcher dispatcher;
      Input input;
      FileSystem filesystem("Piepsii", "papaya");
      TextureStorage textures(filesystem);
      Renderer renderer;

      if (!Graphics::init()) {
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

      Vector2 size(10.0f, 10.0f);
      Vector4 texcoord;
      Sprite sprite;
      Color color = Color::White;

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
         renderer.clear(color);

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
