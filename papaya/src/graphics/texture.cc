// texture.cc

#include "graphics/texture.hpp"
#include "platform/debug.hpp"

#include <SDL_opengl.h>
#include <cassert>

namespace papaya {
   namespace {
      constexpr GLenum gl_texture_filter(const Texture::Filter filter)
      {
         switch (filter)
         {
            case Texture::Filter::Nearest: return GL_NEAREST;
            case Texture::Filter::Linear:  return GL_LINEAR;
         }

         return GL_NONE;
      }

      constexpr GLenum gl_texture_address(const Texture::Address address)
      {
         switch (address)
         {
            case Texture::Address::Clamp:  return GL_CLAMP_TO_EDGE;
            case Texture::Address::Repeat: return GL_REPEAT;
            case Texture::Address::Mirror: return GL_MIRRORED_REPEAT;
         }

         return GL_NONE;
      }

      constexpr GLenum gl_texture_format_internal(const Texture::Format format)
      {
         switch (format)
         {
            case Texture::Format::Rgb8:  return GL_RGB8;
            case Texture::Format::Rgba8: return GL_RGBA8;
         }

         return GL_NONE;
      }

      constexpr GLenum gl_texture_format(const Texture::Format format)
      {
         switch (format)
         {
            case Texture::Format::Rgb8:  return GL_RGB;
            case Texture::Format::Rgba8: return GL_RGBA;
         }

         return GL_NONE;
      }
   } // !anon

   Texture::Texture()
      : id_(0)
      , width_(0)
      , height_(0)
   {
   }

   unsigned int Texture::handle() const
   {
      return id_;
   }

   bool Texture::is_valid() const
   {
      return id_ != 0;
   }

   int Texture::width() const
   {
      return width_;
   }

   int Texture::height() const
   {
      return height_;
   }

   bool Texture::create(const Format format, 
                        const int width, 
                        const int height, 
                        const void *data, 
                        const Filter filter, 
                        const Address address)
   {
      if (is_valid()) {
         destroy();
      }

      GLuint id = 0;
      glGenTextures(1, &id);
      glBindTexture(GL_TEXTURE_2D, id);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_texture_filter(filter));
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_texture_filter(filter));
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_texture_address(address));
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_texture_address(address));
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   gl_texture_format_internal(format),
                   width,
                   height,
                   0,
                   gl_texture_format(format),
                   GL_UNSIGNED_BYTE,
                   data);

      GLenum errcode = glGetError();
      if (errcode != GL_NO_ERROR) {
         glDeleteTextures(1, &id);

         Debug::log("OpenGL error when creating texture: %d", errcode);
         assert(false);

         return false;
      }

      id_ = id;
      width_ = width;
      height_ = height;

      return is_valid();
   }

   void Texture::destroy()
   {
      if (!is_valid()) {
         return;
      }

      glDeleteTextures(1, &id_);
      id_ = 0;
      width_ = 0;
      height_ = 0;
   }
} // !papaya
