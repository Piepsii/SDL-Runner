// renderer.hpp

#pragma once

#include <vector>
#include <graphics/vertex.hpp>

namespace papaya {
   class Color;
   class Sprite;
   class Transform;
   class Texture;

   class Renderer {
   public:
      Renderer();

      void clear(const Color &color);
      void draw(const Sprite &sprite, const Transform &transform);
      void flush();

   private:
      struct Command {
         Command();

         int count_;
         const Texture *texture_;
      };

      Command command_;
      std::vector<Command> commands_;
      std::vector<Vertex> vertices_;
   };
} // !papaya
