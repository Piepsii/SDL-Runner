#include "scene/transform.hpp"

namespace papaya
{
	Transform::Transform()
		: scale_(1.f, 1.f)
		, rotation_(0.f)
	{

	}

	Transform::Transform(const Vector2 &position)
		: position_(position)
		, scale_(1.f, 1.f)
		, rotation_(0.f)
	{

	}

	Transform Transform::set_origin(Vector2 origin)
	{
		origin_ = origin;
		return *this;
	}
	Transform Transform::set_position(Vector2 position)
	{
		position_ = position;
		return *this;
	}
	Transform Transform::set_scale(Vector2 scale)
	{
		scale_ = scale;
		return *this;
	}
	Transform Transform::set_rotation(float rotation)
	{
		rotation_ = rotation;
		return *this;
	}
}