// collision_component.hpp

#pragma once

#include "components/transform_component.hpp"
#include "game/component.hpp"
#include "math/collision_shapes.hpp"

namespace papaya
{
	class CollisionComponent : public ComponentBase
	{
	public:
		CollisionComponent(GameObject *game_object, ComponentFamilyId id);
		~CollisionComponent();

		void update(const Time &delta_time);
		// todo: allow collision for all shapes
		bool intersect(AxisAlignedBoundingBox other);

		AxisAlignedBoundingBox collision_shape();
		void set_collision_shape(Vector2 half);
		bool is_colliding();

	private:
		Transform *transform_;

		AxisAlignedBoundingBox collision_shape_;
		bool is_colliding_;

	};

} // !papaya
