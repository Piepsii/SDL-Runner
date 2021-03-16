// transform_component.hpp

#pragma once

#include "game/component.hpp"
#include "scene/transform.hpp"

namespace papaya
{
	class TransformComponent : public ComponentBase
	{
	public:
		TransformComponent(GameObject *game_object, const ComponentFamilyId id);
		 ~TransformComponent();

		 void update(const Time &delta_time);
		 void render(Renderer &renderer);

		Transform transform_;

	};
} // !papaya
