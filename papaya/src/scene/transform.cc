// transform.cc

#include "scene/transform.hpp"

namespace papaya {
   Transform::Transform()
      : scale_(1.0f, 1.0f)
      , rotation_(0.0f)
   {
   }

   Transform::Transform(const Vector2 &position)
      : position_(position)
      , scale_(1.0f, 1.0f)
      , rotation_(0.0f)
   {
   }

   Transform &Transform::set_origin(const Vector2 &origin)
   {
      origin_ = origin;
      return *this;
   }

   Transform &Transform::set_position(const Vector2 &position)
   {
      position_ = position;
      return *this;
   }

   Transform &Transform::set_scale(const Vector2 &scale)
   {
      scale_ = scale;
      return *this;
   }

   Transform &Transform::set_rotation(const float rotation)
   {
      rotation_ = rotation;
      return *this;
   }
} // !papaya
