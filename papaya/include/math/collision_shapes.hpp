// collision_shapes.hpp

#pragma once

#include "math/vector2.hpp"

namespace papaya
{
   struct LineSegment
   {
      Vector2 start_;
      Vector2 end_;
   };

   struct BoundingCircle
   {
      Vector2 center_;
      float radius_;
   };

   struct AxisAlignedBoundingBox
   {
      Vector2 center_;
      Vector2 half_;
   };

   struct ObjectOrientedBoundingBox
   {
      Vector2 center_;
      Vector2 half_;
      float rotation_;
   };
} // !papaya
