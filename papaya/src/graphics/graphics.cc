// graphics.cc

#include "graphics/graphics.hpp"
#include "graphics/vertex.hpp"
#include "graphics/texture.hpp"

#include "math/color.hpp"
#include "math/rectangle.hpp"
#include "math/matrix4.hpp"

#include <SDL_opengl.h>
#include <cassert>

namespace papaya {
   namespace {
      Texture white;
   } // !anon

   bool Graphics::init(int &width, int &height)
   {
      glEnable(GL_TEXTURE_2D);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);

      set_viewport(Rectangle{ 0, 0, width, height });
      set_projection(Matrix4::orthographic(static_cast<float>(width), static_cast<float>(height)));
      
      unsigned int data[] = { 0xffffffff }; // 0xaarrggbb
      if (!white.create(Texture::Format::Rgba8, 1, 1, data)) {
         return false;
      }

      return true;
   }

   void Graphics::shut()
   {
      white.destroy();
   }

   void Graphics::clear(const Color &color)
   {
      glClearColor(color.r_, color.g_, color.b_, color.a_);
      glClear(GL_COLOR_BUFFER_BIT);
   }

   void Graphics::set_viewport(const Rectangle &rect)
   {
      glViewport(rect.x_, rect.y_, rect.width_, rect.height_);
   }

   void Graphics::set_projection(const Matrix4 &projection)
   {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glMultMatrixf(&projection.x_.x_);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
   }

   void Graphics::render(const Texture *texture, const int count, const Vertex *vertices)
   {
      assert( ((count % 4) == 0) );
      glBindTexture(GL_TEXTURE_2D, texture ? texture->handle() : white.handle());

#if 1
      const char *base = reinterpret_cast<const char *>(vertices);
      glVertexPointer(2,   GL_FLOAT, sizeof(Vertex), reinterpret_cast<const GLvoid *>(base + offsetof(Vertex, position_)));
      glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<const GLvoid *>(base + offsetof(Vertex, texcoord_)));
      glColorPointer(4,    GL_FLOAT, sizeof(Vertex), reinterpret_cast<const GLvoid *>(base + offsetof(Vertex, color_)));
      glDrawArrays(GL_QUADS, 0, count);
#else
      glBegin(GL_QUADS); 
      {
         for (int index = 0; index < count; index++) {
            glColor4f(vertices[index].color_.r_,
                      vertices[index].color_.g_, 
                      vertices[index].color_.b_, 
                      vertices[index].color_.a_);

            glTexCoord2f(vertices[index].texcoord_.x_,
                         vertices[index].texcoord_.y_);

            glVertex2f(vertices[index].position_.x_, 
                       vertices[index].position_.y_);
         }
      }
      glEnd();
#endif
   }
} // !papaya
