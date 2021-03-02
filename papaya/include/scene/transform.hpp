#pragma once

#include <math/vector2.hpp>

namespace papaya
{
	class Transform
	{
	public:
		Transform();
		Transform(const Vector2 &position);

		Transform set_origin(Vector2 origin);
		Transform set_position(Vector2 position);
		Transform set_scale(Vector2 scale);
		Transform set_rotation(float rotation);

		Vector2 origin_;
		Vector2 position_;
		Vector2 scale_;
		float rotation_;
	};
} // !papaya