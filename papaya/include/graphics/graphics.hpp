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
      static bool init();
      static void shut();

      //Flush render view with color.
      static void clear(const Color &color);
      static void set_viewport(const Rectangle &rect);
      static void set_projection(const Matrix4 &projection);
      // Draw texture at coordinates.
      // count: has to be a multiple of 4
      static void render(const Texture *texture, const int count, const Vertex *vertices);
   };
} // !papaya
