// window.hpp

#pragma once

namespace papaya {
   class Window {
   public:
      Window(const char *title,
             const int width,
             const int height);
      ~Window();

      void present();

      static int width_;
      static int height_;

   private:
      void *window_;
      void *context_;
   };
} // !papaya
