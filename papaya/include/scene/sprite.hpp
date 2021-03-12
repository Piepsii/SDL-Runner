// sprite.hpp

#pragma once

#include <math/color.hpp>
#include <math/rectangle.hpp>
#include <math/vector2.hpp>
#include <math/vector4.hpp>

namespace papaya {
   class Texture;

   class Sprite {
   public:
      Sprite();
      Sprite(const Vector2 &size, const Vector4 &texcoord);
      Sprite(const Vector2 &size, const Vector4 &texcoord, const Texture *texture);
      Sprite(const Rectangle &rect, const Texture *texture);

      bool is_valid() const;
      bool has_texture() const;

      void set_color(const Color &color);
      void set_size(const Vector2 &size);
      void set_texcoord(const Vector4 &texcoord);
      void set_texture(const Texture *texture);

      const Color &get_color() const;
      const Vector2 &get_size() const;
      const Vector4 &get_texcoords() const;
      const Texture *get_texture() const;

   private:
      Color color_;
      Vector2 size_;
      Vector4 texcoords_;
      const Texture *texture_;
   };
} // !papaya
