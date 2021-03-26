// collision_component.hpp

#pragma once

#include "components/transform_component.hpp"
#include "components/scrollable_component.hpp"
#include "game/component.hpp"
#include "graphics/texture.hpp"
#include "math/collision_shapes.hpp"
#include "scene/sprite.hpp"
#include "scene/renderer.hpp"

namespace runner
{
	class CollisionComponent : public papaya::ComponentBase
	{
	public:
		CollisionComponent(papaya::GameObject *game_object, papaya::ComponentFamilyId id);
		~CollisionComponent();

		void update(const papaya::Time &delta_time);
		void render(papaya::Renderer &renderer);
		// todo: allow collision for all shapes
		bool intersect(papaya::AxisAlignedBoundingBox other);

		papaya::AxisAlignedBoundingBox collision_shape();
		void set_collision_shape(papaya::Vector2 half);
		bool is_colliding();

	private:
		papaya::Transform *transform_;

		papaya::AxisAlignedBoundingBox collision_shape_;
		bool is_colliding_;
		papaya::Sprite collision_sprite_;

	};

} // !runner
