// game_run.cc

#include <papaya.hpp>

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

      // todo: replace with actual game class!
      Game game(runtime);
      if( !game.init() )
      {
         Debug::log("Failed to initialize game!");
         return 0;
      }

      bool running = true;
      while (running) {
         input.update();
         if (!dispatcher.update()) {
            running = false;
         }

         auto dt = runtime.deltaTime();
         if( !game.tick(dt) )
         {
            running = false;
         }

         window.present();
      }

      game.shut();
      Graphics::shut();
   } 
   catch (std::exception &e) {
      (void)e;
   }

   return 0;
}
