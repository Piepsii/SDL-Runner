// window.cc

#include "platform/window.hpp"

#include <SDL.h>
#include <stdexcept>

namespace papaya {
   Window::Window(const char *title,
                  const int width,
                  const int height)
      : window_(nullptr)
      , context_(nullptr)
   {

      if ((window_ = SDL_CreateWindow(title,
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      width,
                                      height,
                                      SDL_WINDOW_OPENGL)) == nullptr)
      {
         throw std::runtime_error("Could not create window!");
      }

      if ((context_ = SDL_GL_CreateContext(static_cast<SDL_Window *>(window_))) == nullptr) 
      {
         throw std::runtime_error("Could not create OpenGL render context!");
      }

      width_ = width;
      height_ = height;
   }

   int Window::width_;
   int Window::height_;

   Window::~Window()
   {
      SDL_GL_MakeCurrent(nullptr, nullptr);
      SDL_GL_DeleteContext(context_);
      SDL_DestroyWindow(static_cast<SDL_Window *>(window_));
   }

   void Window::present() 
   {
      SDL_GL_SwapWindow(static_cast<SDL_Window *>(window_));
   }
} // !papaya
