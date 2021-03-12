// transform.hpp

#pragma once

#include <math/vector2.hpp>

namespace papaya {
   class Transform {
   public:
      Transform();
      Transform(const Vector2 &position);

      Transform &set_origin(const Vector2 &origin);
      Transform &set_position(const Vector2 &position);
      Transform &set_scale(const Vector2 &scale);
      Transform &set_rotation(const float rotation);

      Vector2 origin_; // pivot
      Vector2 position_;
      Vector2 scale_;
      float rotation_;
   };
} // !papaya
