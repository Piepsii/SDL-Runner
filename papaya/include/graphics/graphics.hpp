// graphics.hpp

#pragma once

namespace papaya {
   class Color;
   class Rectangle;
   class Matrix4;
   class Vertex;
   class Texture;

   class Graphics {
   public:
      static bool init(int &width, int &height);
      static void shut();

      static void clear(const Color &color);
      static void set_viewport(const Rectangle &rect);
      static void set_projection(const Matrix4 &projection);
      static void render(const Texture *texture, const int count, const Vertex *vertices);
   };
} // !papaya
