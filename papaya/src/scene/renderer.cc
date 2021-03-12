// renderer.cc

#include "scene/renderer.hpp"
#include "scene/sprite.hpp"
#include "scene/transform.hpp"
#include "graphics/graphics.hpp"
#include "graphics/texture.hpp"
#include "math/color.hpp"
#include "math/vector4.hpp"
#include "math/matrix3.hpp"

#include <cmath>

namespace papaya {
   namespace {
      Matrix3 from_transform(const Transform &transform)
      {
         const Vector2 origin   = transform.origin_;
         const Vector2 position = transform.position_;
         const Vector2 scale    = transform.scale_;
         const float rotation   = transform.rotation_;

         const float a = -rotation * 3.141592654f / 180.f;
         const float c = std::cosf(a);
         const float s = std::sinf(a);
         const float xc = scale.x_ * c;
         const float yc = scale.y_ * c;
         const float xs = scale.x_ * s;
         const float ys = scale.y_ * s;
         const float tx = -origin.x_ * xc - origin.y_ * ys + position.x_;
         const float ty =  origin.x_ * xs - origin.y_ * yc + position.y_;

         return
         {
              xc,   ys,   tx,
             -xs,   yc,   ty,
            0.0f, 0.0f, 1.0f,
         };
      }
   } // !anon

   Renderer::Command::Command()
      : count_(0)
      , texture_(nullptr)
   {
   }

   Renderer::Renderer()
   {
      vertices_.reserve(4 * 1024);
   }

   void Renderer::clear(const Color &color)
   {
      Graphics::clear(color);
   }

   void Renderer::draw(const Sprite &sprite, const Transform &transform)
   {
      if (command_.texture_ != sprite.get_texture()) {
         if (command_.count_ != 0) {
            commands_.push_back(command_);
         }

         command_.count_ = 0;
         command_.texture_ = sprite.get_texture();
      }

      command_.count_ += 4;

      const Color &color = sprite.get_color();
      const Vector2 &size = sprite.get_size();
      const Vector4 &texcoords = sprite.get_texcoords();

      Vertex vertices[] =
      {
         { {    0.0f,    0.0f, }, { texcoords.x_, texcoords.y_ }, color },
         { { size.x_,    0.0f, }, { texcoords.z_, texcoords.y_ }, color },
         { { size.x_, size.y_, }, { texcoords.z_, texcoords.w_ }, color },
         { {    0.0f, size.y_, }, { texcoords.x_, texcoords.w_ }, color },
      };

      const Matrix3 world = from_transform(transform);
      for (auto &vert : vertices) {
         vert.position_ = transform_vector(world, vert.position_);
         vertices_.push_back(vert);
      }
   }

   void Renderer::flush()
   {
      if (command_.count_ != 0) {
         commands_.push_back(command_);
         command_ = {};
      }

      if (commands_.empty()) {
         return;
      }

      int offset = 0;
      for (auto &it : commands_) {
         Graphics::render(it.texture_, it.count_, vertices_.data() + offset);
         offset += it.count_;
      }

      vertices_.clear();
      commands_.clear();
   }
} // !papaya
